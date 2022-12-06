#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <vector>

// Custom widget for displaying the image and path
class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    ImageWidget(QWidget *parent = nullptr) : QWidget(parent) {}

    void setImage(const QPixmap& image)
    {
        initH = image.height();
        initW = image.width();
        this->image = image.scaled(500, 500, Qt::KeepAspectRatio);
        update();
    }

    void setPath(const std::vector<std::pair<int, int>>& path)
    {
        this->path = path;
        update();
    }

protected:
//    void paintEvent(QPaintEvent* event)
//    {
//        QPainter painter(this);

//        // Draw the image
//        painter.drawPixmap(0, 0, image);

//        // Draw the path on top of the image
//        QPen pen(Qt::red);
//        pen.setWidth(1);
//        painter.setPen(pen);
//        for (auto point : path)
//        {
//            painter.drawPoint(point.first, point.second);
//        }
//    }

    void paintEvent(QPaintEvent* event)
    {
        // Create a QPainter object
        QPainter painter(this);

        // Draw the image
        painter.drawPixmap(0, 0, image);

        // Scale the path coordinates
        QVector<QPoint> scaledPath;
        for (const auto& point : path)
        {
            scaledPath.append(QPoint(point.first * image.width() / initW, point.second * image.height() / initH));
        }

        // Save the painter state
        painter.save();

        // Scale the painter
        painter.scale(image.width() / initW, image.height() / initH);

        // Draw the path
        painter.setPen(QPen(Qt::red, 1));
        for (auto point : path)
        {
            painter.drawPoint(point.first, point.second);
        }

        // Restore the painter state
        painter.restore();
    }



private:
    QPixmap image;
    std::vector<std::pair<int, int>> path;
    int initH;
    int initW;
};


#endif // IMAGEWIDGET_H
