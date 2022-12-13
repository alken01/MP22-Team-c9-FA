#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QWheelEvent>
#include <QKeyEvent>
#include <iostream>
#include <vector>

// Custom widget for displaying the image and path
class ImageWidget: public QWidget
{
    Q_OBJECT

public:
    ImageWidget(QWidget* parent = nullptr) : QWidget(parent){}

    void setImage(const QPixmap& image){
        this->image = image;
        int scale = 700;
        scaledImage = image.scaled(scale, scale, Qt::KeepAspectRatio);
        update();
    }

    void setPath(const std::vector<std::pair<int, int>>& path){
        this->path = path;
        update();
    }

    void moveImage(int dx, int dy){
        // Update the position of the image
        imageX += dx;
        imageY += dy;

        // Update the path coordinates
        for(auto& point : path){
            point.first += dx;
            point.second += dy;
        }

        // Trigger a repaint of the widget
        update();
    }

protected:
    void wheelEvent(QWheelEvent* event){
        // Calculate the zoom factor based on the scroll wheel delta
        QPoint numDegrees = event->angleDelta() / 8;
        int numSteps = numDegrees.y() / 15;
        zoomFactor += numSteps * 0.1;

        // Clamp the zoom factor to the range [1, 2]
        zoomFactor = std::max(1.0, std::min(zoomFactor, 5.0));

        // Update the scaled image
        scaledImage = image.scaled(zoomFactor * image.width(), zoomFactor * image.height(), Qt::KeepAspectRatio);

        // Trigger a repaint of the widget
        update();
    }

    void paintEvent(QPaintEvent* event){
        // Create a QPainter object
        QPainter painter(this);

        // Draw the scaled image
        painter.drawPixmap(imageX, imageY, scaledImage);

        // Scale the path coordinates
        QVector<QPoint> scaledPath;
        for(const auto& point : path){
            scaledPath.append(QPoint(point.first * image.width(), point.second * image.height()));
        }

        // Save the painter state
        painter.save();

        // Scale the painter
        painter.scale(scaledImage.width() / image.width(), scaledImage.height() / image.height());

        // Draw the path
        painter.setPen(QPen(Qt::blue, 3));
        for(auto point : path){
            painter.drawPoint(point.first, point.second);
        }

        //
        // Restore the painter state
        painter.restore();
    }

    void keyPressEvent(QKeyEvent* event){
        // Handle the arrow keys
        if(event->key() == Qt::Key_Right){
            moveImage(-10, 0); // Move the image 10 pixels to the left
        } else if(event->key() == Qt::Key_Left){
            moveImage(10, 0); // Move the image 10 pixels to the right
        } else if(event->key() == Qt::Key_Down){
            moveImage(0, -10); // Move the image 10 pixels upwards
        } else if(event->key() == Qt::Key_Up){
            moveImage(0, 10); // Move the image 10 pixels downwards
        }
    }

private:
    QPixmap image;
    QPixmap scaledImage;
    std::vector<std::pair<int, int>> path;
    double zoomFactor = 1.0;
    int imageX = 0;
    int imageY = 0;
};
