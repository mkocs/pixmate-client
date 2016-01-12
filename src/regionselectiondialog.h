#ifndef REGIONSELECTIONDIALOG_H
#define REGIONSELECTIONDIALOG_H

#include <QDialog>
#include <QPainter>
#include <QPixmap>
#include <QRect>
#include <QPointer>

class RegionSelectionDialog : public QDialog
{
public:
	// Initializes the Dialog. Takes the parent
	// widget as an argument to pass on to the
	// QDialog constructor to attach the dialog
	// to the parent widget
	RegionSelectionDialog(QWidget *parent = 0);
	~RegionSelectionDialog();
	// Returns the selected area as a pixmap.
	// Called from the main window when the
	// new screenshot button is pressed.
	QPixmap GetSelectionPixmap();

protected:
	// Reimplementation of QObject's event() function.
	// Closes or continues the dialog based on the user input.
	// If the user pressed any other button than the left
	// mouse button, it hides the dialog.
	bool event(QEvent *event);
	void paintEvent(QPaintEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

private:
	// Initializes the QPainter, then calls
	// the different draw functions and passes
	// the painter.
	void DrawOverlay();

	// Draws the background from a Pixmap
	// of the primary screen.
	// A screenshot is shown to the user as
	// the background to offer a visual representation
	// of the selected region.
	void DrawBackground(QPainter &painter);
	// Draws the text explaining how to use the region
	// selection and its surrounding box positioned at
	// the top of the screen.
	void DrawToolTipTextRectangle(QPainter &painter);
	// Draws the background rectangle surrounding
	// the tooltip text
	void DrawToolTipTextBackground(QRect textrectangle, QString texttooltip, QPainter &painter);
	void DrawToolTipText(QRect textbackgroundrectangle, QString texttooltip, QPainter &painter);
	// Sets the widget's palette (color group) to the
    // screenshot pixmap that is taken in the constructor
    // after drawing the overlay.
    // Otherwise the dialog would appear as a blank
    // field.
	void SetWidgetPalette();
	// Draws the rectangle around the selected area
	// when the user presses the left mouse button until
	// he releases it.
	void DrawSelectionRectangle(QPainter &painter);
	void DrawSelectionResolutionText(QPainter &painter);
	void DrawSelectionZoomBox(QPainter &painter);
	
	QPixmap desktop_background_pixmap_;
	QPixmap desktop_color_pixmap_;
	bool backgroundexists_;
	QRect selection_rectangle_;
	QPoint selection_startpoint_;
	QPoint selection_endpoint_;
};
#endif
