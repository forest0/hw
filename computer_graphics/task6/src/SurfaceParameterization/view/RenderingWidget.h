#ifndef RENDERINGWIDGET_H
#define RENDERINGWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <QtCore/QEvent>
#include "../model/HE_mesh/Vec.h"
#include "../model/parameterization/Parameterizer.h"

using trimesh::vec;
using trimesh::point;

class MainWindow;
class CArcBall;
class Mesh3D;

class RenderingWidget : public QGLWidget
{
    Q_OBJECT

public:
    RenderingWidget(QWidget *parent, MainWindow* mainwindow=0);
    ~RenderingWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void timerEvent(QTimerEvent *e);

    // mouse events
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);

public:
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);

signals:
    void meshInfo(int, int, int);
    void operatorInfo(QString);

private:
    void Render();
    void SetLight();

public slots:
    void SetBackground();
    void ReadMesh();
    void WriteMesh();
    void LoadTexture();

    void Debug();

    void CheckDrawPoint(bool bv);
    void CheckDrawEdge(bool bv);
    void CheckDrawFace(bool bv);
    void CheckLight(bool bv);
    void CheckDrawTexture(bool bv);
    void CheckDrawAxes(bool bv);

    void CheckUniform(bool bv);
    void CheckWeightedLeastSquares(bool bv);
    void CheckShapePreserving(bool bv);

    void CheckShowVerticesCoordinate(bool bv);
    void CheckShowParameterizedCoordinate(bool bv);


private:
    void DrawAxes(bool bv);
    void DrawPoints(bool);
    void DrawEdge(bool);
    void DrawFace(bool);
    void DrawTexture(bool);

public:
    MainWindow            *ptr_mainwindow_;
    CArcBall              *ptr_arcball_;
    Mesh3D                *ptr_mesh_;

    // Texture
    GLuint                texture_[1];
    bool                  is_load_texture_;

    // eye
    GLfloat               eye_distance_;
    point                 eye_goal_;
    vec                   eye_direction_;
    QPoint                current_position_;

    // Render information
    bool                  is_draw_point_;
    bool                  is_draw_edge_;
    bool                  is_draw_face_;
    bool                  is_draw_texture_;
    bool                  has_lighting_;
    bool                  is_draw_axes_;

    // Parameterization information
    
    ParameterizationMethod parameterizationMethod;

private:
    bool isVerticesCoordinateShown;
};

#endif // RENDERINGWIDGET_H
