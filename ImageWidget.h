#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QWheelEvent>
#include <iostream>
#include <vector>

// Custom widget for displaying the image and path
class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    ImageWidget(QWidget *parent = nullptr) : QWidget(parent) {}

    void setImage(const QPixmap& image)
    {
        this->image = image;
        scaledImage = image.scaled(500, 500, Qt::KeepAspectRatio);
        update();
    }

    void setPath(const std::vector<std::pair<int, int>>& path)
    {
        this->path = path;
        update();
    }

protected:

    void wheelEvent(QWheelEvent* event)
    {
        // Calculate the zoom factor based on the scroll wheel delta
        QPoint numDegrees = event->angleDelta() / 8;
        int numSteps = numDegrees.y() / 15;
        zoomFactor += numSteps * 0.1;

        // Clamp the zoom factor to the range [0.1, 2.0]
        zoomFactor = std::max(0.1, std::min(zoomFactor, 2.0));

        // Update the scaled image
        scaledImage = image.scaled(zoomFactor * image.width(), zoomFactor * image.height(), Qt::KeepAspectRatio);

        // Trigger a repaint of the widget
        update();
    }

    void paintEvent(QPaintEvent* event)
    {
        // Create a QPainter object
        QPainter painter(this);

        // Draw the scaled image
        painter.drawPixmap(0, 0, scaledImage);

        // Scale the path coordinates
        QVector<QPoint> scaledPath;
        for (const auto& point : path){
            scaledPath.append(QPoint(point.first * scaledImage.width() / image.width(), point.second * scaledImage.height() / image.height()));
        }

        // Save the painter state
        painter.save();

        // Scale the painter
        painter.scale(scaledImage.width() / image.width(), scaledImage.height() / image.height());

        // Draw the path
        painter.setPen(QPen(Qt::blue, 30));
        for (auto point : path){
            painter.drawPoint(point.first, point.second);
        }

        // Restore the painter state
        painter.restore();
    }

private:
    QPixmap image;
    QPixmap scaledImage;
    std::vector<std::pair<int, int>> path;
    double zoomFactor = 1.0;
};
