#ifndef TEST_WIDGET_H_
#define TEST_WIDGET_H_

// QT libraries
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

namespace test
{
  class TestWidget : public QOpenGLWidget, protected QOpenGLFunctions
  {
    Q_OBJECT

  public:
    explicit TestWidget(QWidget *parent = 0);
    ~TestWidget();

    void UpdateView();
    void ReorderDisplays();
  Q_SIGNALS:
    void Hover(double x, double y, double scale);

  protected:
    void initializeGL();
    void initGlBlending();
    void pushGlMatrices();
    void popGlMatrices();
    void paintEvent(QPaintEvent* event);

    void InitializePixelBuffers();

    bool has_pixel_buffers_;
    int32_t pixel_buffer_size_;
    GLuint pixel_buffer_ids_[2];
    int32_t pixel_buffer_index_;
    bool capture_frames_;

    bool initialized_;
    bool fix_orientation_;
    bool rotate_90_;
    bool enable_antialiasing_;

  };
}

#endif  // TEST_WIDGET_H_
