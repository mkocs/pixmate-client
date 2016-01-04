#include "src/regionselect.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QtGlobal>
#include <QtMath>

RegionSelect::RegionSelect(QWidget *parent):QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setWindowState(Qt::WindowFullScreen);
    setCursor(Qt::CrossCursor);

    sizeDesktop = QApplication::desktop()->size();
    resize(sizeDesktop);

    QScreen *screen = QGuiApplication::primaryScreen();
    if(screen)
      desktopPixmapBkg = screen->grabWindow(QApplication::desktop()->winId());
    //desktopPixmapBkg = QScreen::grabWindow(QApplication::desktop()->winId());
    desktopPixmapClr = desktopPixmapBkg;

    move(0,0);
    drawBackground();
}

RegionSelect::~RegionSelect() {}

bool RegionSelect::event(QEvent *event)
{
    if(event->type() == QEvent::MouseButtonRelease ||
            event->type() == QEvent::KeyPress)
        accept();
    if(event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if(mouseEvent->button() != Qt::LeftButton)
            reject();
        selectionStartPoint = mouseEvent->pos();
        selectRect = QRect(selectionStartPoint, QSize());
    }
    return QDialog::event(event);
}

void RegionSelect::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(!background)
        painter.drawPixmap(QPoint(0,0), desktopPixmapBkg);
    drawRectSelection(painter);
}

void RegionSelect::mouseMoveEvent(QMouseEvent *event)
{
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    selectRect = QRect(selectionStartPoint, mouseEvent->pos()).normalized();
    selectionEndPoint = mouseEvent->pos();
    update();
}

void RegionSelect::drawBackground()
{
    // Create painter on pixelmap
    // of desktop
    QPainter painter(&desktopPixmapBkg);

    // Set painter brush to 85% transparency
    painter.setBrush(QBrush(QColor(0, 0, 0, 85), Qt::SolidPattern));

    // Draw rectangle of desktop size with painter
    painter.drawRect(QApplication::desktop()->rect());

    QRect txtRect = QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen());
    QString txtToolTip = QApplication::tr("Use your mouse to select a region or\nexit by pressing any other key");
    float txtRectHeight = txtRect.height();
    txtRect.setHeight(qRound(txtRectHeight / 10));


    painter.setPen(QPen(Qt::red));
    painter.setBrush(QBrush(QColor(255, 255, 255, 180), Qt::SolidPattern));
    QRect txtBgRect = painter.boundingRect(txtRect, Qt::AlignCenter, txtToolTip);

    // Set height & width of background rectangle
    txtBgRect.setX(txtBgRect.x() - 6);
    txtBgRect.setY(txtBgRect.y() - 4);
    txtBgRect.setWidth(txtBgRect.width() + 12);
    txtBgRect.setHeight(txtBgRect.height() + 8);

    painter.drawRect(txtBgRect);

    // Draw text
    painter.setPen(QPen(Qt::black));
    painter.drawText(txtBgRect, Qt::AlignCenter, txtToolTip);

    background = (qApp->desktop()->numScreens() > 1);
    if(background)
    {
        QPalette newPalette = palette();
        newPalette.setBrush(QPalette::Window, QBrush(desktopPixmapBkg));
        setPalette(newPalette);
    }
}

void RegionSelect::drawRectSelection(QPainter &painter)
{
    painter.drawPixmap(selectRect, desktopPixmapClr, selectRect);
    painter.setPen(QPen(QBrush(QColor(0, 0, 0, 255)), 2));
    painter.drawRect(selectRect);

    QString txtSize = QApplication::tr("%1 x %2 pixels ").arg(selectRect.width()).arg(selectRect.height());
    painter.drawText(selectRect, Qt::AlignBottom | Qt::AlignRight, txtSize);

    if(!selectionEndPoint.isNull())
    {
        const quint8 zoomSide = 200;

        // Create magnifier coordinates
        QPoint zoomStart = selectionEndPoint;
        zoomStart -= QPoint(zoomSide/5, zoomSide/5);

        QPoint zoomEnd = selectionEndPoint;
        zoomEnd += QPoint(zoomSide/5, zoomSide/5);

        // Create rectangle area for magnifier
        QRect zoomRect = QRect(zoomStart, zoomEnd);

        QPixmap zoomPixmap = desktopPixmapClr.copy(zoomRect).scaled(QSize(zoomSide, zoomSide), Qt::KeepAspectRatio);

        QPainter zoomPainter(&zoomPixmap);
        zoomPainter.setPen(QPen(QBrush(QColor(255, 0, 0, 180)), 2));
        zoomPainter.drawRect(zoomPixmap.rect()); // draw
        zoomPainter.drawText(zoomPixmap.rect().center() - QPoint(4, -4), "+");

        QPoint zoomCenter = selectRect.bottomRight();
        if(zoomCenter.x() + zoomSide > desktopPixmapClr.rect().width() ||
                zoomCenter.y() + zoomSide > desktopPixmapClr.rect().height())
            zoomCenter -= QPoint(zoomSide, zoomSide);
        painter.drawPixmap(zoomCenter, zoomPixmap);
    }
}

QPixmap RegionSelect::getSelection()
{
    QPixmap sel;
    sel = desktopPixmapClr.copy(selectRect);
    return sel;
}





