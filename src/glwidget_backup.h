#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QBrush>
#include <QFont>
#include <QImage>
#include <QPen>
#include <QGLWidget>
#include <QTimer>

#include <vector>

#include "modedialog.h"
#include "graph.h"
#include "badgedatareader.h"
#include "ubidatareader.h"
#include "forceatlas2.h"

#include "qtlogo.h"

enum data_src_type {SRC_BADGE, SRC_UBI, SRC_COMBINED};


class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

public slots:
    void mainLoop();
    void updateGraph();
    void setTimeMode(mode_type);
    void setSrcMode(data_src_type);

protected:
    void initializeGL();
    void paintEvent(QPaintEvent *event);
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void showEvent(QShowEvent *event);
    void wheelEvent(QWheelEvent *event);

private slots:
//    void animate();

private:

    void setupViewport(int width, int height);
    void initDataReaders();


    QWidget *parent;
    Graph *graph;
    Graph *prev_graph;

    BadgeDataReader *bdr;
    UbiDataReader *udr;

    ForceAtlas2 *fa2;

    float ubi_radius;

//    QTimer fa2_timer;

    string default_reading_location;

    QTimer graph_update_timer;
    QTimer fa2_timer;

    QPoint view_center;

    QColor backgroundColor;
    GLuint object;

    QPoint lastMousePos;
    std::vector<QVertex *> vertices;

    float scale;

    mode_type time_mode;
    data_src_type src_mode;

    QtLogo *logo;




};

#endif
