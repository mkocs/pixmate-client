#ifndef REGIONSELECT_H
#define REGIONSELECT_H

#include <QDialog>
#include <QSize>
#include <QScreen>
#include <QMouseEvent>
#include <QPainter>
#include <QRect>
#include <QBrush>
#include <QColor>
#include <QPen>
#include <QPalette>

class RegionSelect : public QDialog
{
public:
    RegionSelect(QWidget *parent = 0);
    ~RegionSelect();
    QPixmap getSelection();

protected:
    bool event(QEvent *event);
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QRect selectRect;
    QSize sizeDesktop;

    QPoint selectionStartPoint;
    QPoint selectionEndPoint;

    bool background;

    QPixmap desktopPixmapBkg;
    QPixmap desktopPixmapClr;

    void drawBackground();
    void drawRectSelection(QPainter &painter);
};

#endif // REGIONSELECT_H
