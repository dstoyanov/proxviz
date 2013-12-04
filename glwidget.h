/*
 * Copyright 2013 Dimo Stoyanov
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QBrush>
#include <QFont>
#include <QImage>
#include <QPen>
#include <QGLWidget>
#include <QTimer>
#include <map>

#include "badgedatareader.h"
#include "ubidatareader.h"
#include "modedialog.h"
#include "graph.h"
#include "forceatlas2.h"
#include "mainwindow.h"

enum data_src_type {SRC_BADGE, SRC_UBI, SRC_COMBINED};

class MainWindow;

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();
    void setUbiRadius(double r);

signals:
    void setNumberEdgesLabel(int n);
    void setNumberVerticesLabel(int n);
    void setTimeLabel(time_t *t);
    void setSliderMax(int i);


public slots:
    void setTimeMode(mode_type mode);
    void setSrcMode(int mode);
    void sliderValueChanged(int v);



protected:
    void initializeGL();
    void paintEvent(QPaintEvent *event);
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
//    void showEvent(QShowEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
//    void createBubbles(int number);
//    void drawInstructions(QPainter *painter);
    void setupViewport(int width, int height);
    void initDataReaders();
    void readUbiToBadgeMap(string filename);

    double distance;

    float scale;
    float translateX;
    float translateY;

    float ubi_scale; //used to scale the ubisense, so they fit the canvas

    QWidget *parent;

    BadgeDataReader *bdr;
    UbiDataReader *udr;

    Graph *badge_graph;
    Graph *ubi_graph;

    ForceAtlas2 *fa2;

    double ubi_radius;

    QTimer fa2_timer;
    QTimer graph_update_timer;

    string default_reading_location;

    mode_type time_mode;
    data_src_type src_mode;

    std::map<string, string> ubi_to_badge_map;
    std::map<string, string> badge_to_ubi_map;

    QTransform painter_to_scene_transform;


private slots:
    void updateLayout();
    void updateGraph();

};

#endif
