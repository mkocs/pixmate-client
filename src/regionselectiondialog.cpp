#include "src/regionselectiondialog.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QtGlobal>
#include <QPen>
#include <QBrush>
#include <QPoint>
#include <QPalette>
#include <QScreen>
#include <QMouseEvent>
#include <QString>

// Sets necessary window flags to make the dialog frameless, maximized/fullscreen
// and to make it stay on top.
// Apple's OSX by default hides its top bar and dock when an application goes
// fullscreen. To avoid that, the dialog won't be fullscreen, but maximized
// on Apple devices.
// Also sets the cursor to a selection cross.
//
// Gets the primary screen and fetches a pixmap of the given
// window (0, can be changed to fetch a pixmap of another screen) and assigns
// it to the variable that will serve as background.
RegionSelectionDialog::RegionSelectionDialog(QWidget *parent) : QDialog(parent) {
	// See http://doc.qt.io/qt-5/qt.html for further information.
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	#ifdef __APPLE__
	setWindowState(Qt::WindowMaximized);
	#else
	setWindowState(Qt::WindowFullScreen);
	#endif

	setCursor(Qt::CrossCursor);

	QScreen *screen = QGuiApplication::primaryScreen();
	if (screen)
		// The value of winId() is the OS-specific window type, depending on your platform:
	    // MSWindows: HWND
		// Mac: HIView
		// X: Window
		desktop_background_pixmap_ = screen->grabWindow(QApplication::desktop()->winId());
	desktop_color_pixmap_ = desktop_background_pixmap_;

	move(0,0);
	draw_overlay();
}

RegionSelectionDialog::~RegionSelectionDialog() {
}

/*
 * <EVENTS>
 */
// Called if any event occurs.
// Returns true if the event was recognized and processed.
// Checks the user's input. If the user released a mouse button or
// pressed a key, accept() hides/ends the dialog and sets its result
// to accepted.
// Otherwise, if the left mouse button has been pressed,
// the function will check whether the pressed button was the left mouse button.
// If not, it hides/ends the dialog and sets its result to rejected.
// Otherwise it will set the selection start point to where the pointer
// was first pressed and either paintEvent or mouseMoveEvent gets called.
bool RegionSelectionDialog::event(QEvent *event) {
	if (event->type() == QEvent::MouseButtonRelease ||
		event->type() == QEvent::KeyPress)
		accept();
	if (event->type() == QEvent::MouseButtonPress) {
		QMouseEvent *mouseevent = static_cast<QMouseEvent*>(event);
		if(mouseevent->button() != Qt::LeftButton)
			reject();
		selection_startpoint_ = mouseevent->pos();
		selection_rectangle_ = QRect(selection_startpoint_, QSize());
	}
	return QDialog::event(event);
}

// Called if there has been a request to repaint all or part of the dialog.
// (In this dialog invoked by an update() call in mouseMoveEvent(QMouseEvent *event))
// Draws the screenshot pixmap from the constructor if there's no background yet
// and draws the selection rectangle afterwards.
void RegionSelectionDialog::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	if(!backgroundexists_)
		painter.drawPixmap(QPoint(0,0), desktop_background_pixmap_);
	draw_selection_rectangle(painter);
}

// Called if there has been a mouse related event.
// Updates the currently selected rectangle to reach from the
// start point (which is set in event(QEvent *event) if there was a
// left mouse button click) to the selection endpoint (the current mouse pointer position).
// normalized() ensures the rectangle has a non-negative width
// and height.
void RegionSelectionDialog::mouseMoveEvent(QMouseEvent *event) {
	QMouseEvent *mouseevent = static_cast<QMouseEvent*>(event);
	selection_rectangle_ = QRect(selection_startpoint_, mouseevent->pos()).normalized();
	selection_endpoint_ = mouseevent->pos();
	update(); // invokes paintEvent(QPaintEvent *)
}
/*
 * </EVENTS>
 */


void RegionSelectionDialog::draw_overlay() {
	QPainter painter(&desktop_background_pixmap_);
	draw_background(painter);
	draw_tooltip_text_rectangle(painter);
	set_widget_palette();
}

// Sets the painter_'s brush to 85% opacity to give a
//× slightly transparent look to the background, draws
// a rectangle with that setting and calls the the set_widget_palette
// function to update the widget's palette to use the screenshot
// pixmap as its background.
void RegionSelectionDialog::draw_background(QPainter &painter) {
	painter.setBrush(QBrush(QColor(0, 0, 0, 85), Qt::SolidPattern));
	painter.drawRect(QApplication::desktop()->rect());
}

void RegionSelectionDialog::draw_tooltip_text_rectangle(QPainter &painter) {
	QRect textrectangle = QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen());
	float textboxheight = textrectangle.height();
   	QString text_tooltip = QApplication::tr("Use your mouse to select a region or\nexit by pressing any other key");
	textrectangle.setHeight(qRound(textboxheight/10));
	draw_tooltip_text_background(textrectangle, text_tooltip, painter);
	draw_tooltip_text(textrectangle, text_tooltip, painter);
}

void RegionSelectionDialog::draw_tooltip_text_background(QRect textrectangle, QString texttooltip, QPainter &painter) {
    QRect textbackgroundrectangle = painter.boundingRect(textrectangle, Qt::AlignCenter, texttooltip);
	textbackgroundrectangle.setX(textbackgroundrectangle.x() - 6);
	textbackgroundrectangle.setY(textbackgroundrectangle.y() - 4);
	textbackgroundrectangle.setWidth(textbackgroundrectangle.width() + 12);
	textbackgroundrectangle.setHeight(textbackgroundrectangle.height() + 8);
	painter.setPen(QPen(Qt::gray));
	painter.setBrush(QBrush(QColor(255, 255, 255, 180), Qt::SolidPattern));
	painter.drawRect(textbackgroundrectangle);
}

void RegionSelectionDialog::draw_tooltip_text(QRect textbackgroundrectangle, QString texttooltip, QPainter &painter) {
	painter.setPen(QPen(Qt::black));
	painter.drawText(textbackgroundrectangle, Qt::AlignCenter, texttooltip);
}

// Takes the dialog's current palette as a base and sets the
// brush color (sort of) to the screenshot pixmap that is taken in the
// constructor.
void RegionSelectionDialog::set_widget_palette() {
	backgroundexists_ = (qApp->desktop()->screenCount() > 1);
	if (backgroundexists_) {
		QPalette newwidgetpalette = palette();
		newwidgetpalette.setBrush(QPalette::Window /*value: 10*/, QBrush(desktop_background_pixmap_));
		setPalette(newwidgetpalette);
	}
}

// Called in case of a paintEvent. Draws/redraws the selection rectangle
// every time there's an update.
// Also calls the function to draw the zoom box and the resolution text
void RegionSelectionDialog::draw_selection_rectangle(QPainter &painter) {
	painter.drawPixmap(selection_rectangle_, desktop_color_pixmap_, selection_rectangle_);
	draw_selection_resolution_text(painter);
	painter.setPen(QPen(QBrush(QColor(0, 0, 0, 0/*alpha channel*/)), 2));
	painter.drawRect(selection_rectangle_);
	draw_selection_zoombox(painter);
}

// Called from draw_selection_rectangle()
// Draws text showing the resolution of the current selection in the lower right corner
// of the selection rectangle.
void RegionSelectionDialog::draw_selection_resolution_text(QPainter &painter) {
	QString text_size = QApplication::tr("%1 x %2 px ").arg(selection_rectangle_.width()).arg(selection_rectangle_.height());
	painter.drawText(selection_rectangle_, Qt::AlignBottom | Qt::AlignRight, text_size);
}

// Called from draw_selection_rectangle()
// Draws a magnified version of the area surrounding the mouse cursor
// to give the user a better idea of where his selection currently
// ends.
void RegionSelectionDialog::draw_selection_zoombox(QPainter &painter) {
	if (!selection_endpoint_.isNull()) {
		const quint8 zoom_side = 200;
		QPoint zoom_startpoint = selection_endpoint_;
		zoom_startpoint -= QPoint(zoom_side/5, zoom_side/5);
		QPoint zoom_endpoint = selection_endpoint_;
		zoom_endpoint += QPoint(zoom_side/5, zoom_side/5);
		QRect zoom_rectangle = QRect(zoom_startpoint, zoom_endpoint);
		QPixmap zoom_pixmap = desktop_color_pixmap_.copy(zoom_rectangle).scaled(QSize(zoom_side, zoom_side), Qt::KeepAspectRatio);
		QPainter zoom_painter(&zoom_pixmap);
		zoom_painter.setPen(QPen(QBrush(QColor(50, 50, 50, 180)), 2));
		zoom_painter.drawRect(zoom_pixmap.rect());
		zoom_painter.drawText(zoom_pixmap.rect().center() - QPoint(4, -4), "+");
		QPoint zoom_center = selection_rectangle_.bottomRight();
		if(zoom_center.x() + zoom_side > desktop_color_pixmap_.rect().width() ||
		   zoom_center.y() + zoom_side > desktop_color_pixmap_.rect().height())
			zoom_center -= QPoint(zoom_side, zoom_side);
		painter.drawPixmap(zoom_center, zoom_pixmap);
	}
}

// Called from mainwindow after creating a RegionSelectionDialog object.
QPixmap RegionSelectionDialog::get_selection_pixmap() {
	QPixmap selection;
  // copy(const QRect &rectangle = QRect()) returns a
  // deep copy of the subset of the pixmap that is specified
  // by the given rectangle.
  // If the given rectangle is empty, the whole image
  // is copied.
	selection = desktop_color_pixmap_.copy(selection_rectangle_);
	return selection;
}
