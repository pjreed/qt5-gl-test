#include <QApplication>
#include <QMainWindow>
#include <QPainter>

#include <test.h>

namespace test
{
TestWidget::TestWidget(QWidget* parent) :
  QOpenGLWidget(parent)
{
}

TestWidget::~TestWidget()
{
}

void TestWidget::initializeGL()
{
  initializeOpenGLFunctions();


  // Check if pixel buffers are available for asynchronous capturing
  std::string extensions = (const char*)glGetString(GL_EXTENSIONS);
  has_pixel_buffers_ = extensions.find("GL_ARB_pixel_buffer_object") != std::string::npos;

  glClearColor(0.58f, 0.56f, 0.5f, 1);
  if (enable_antialiasing_)
  {
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
  }
  else
  {
    glDisable(GL_MULTISAMPLE);
    glDisable(GL_POINT_SMOOTH);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_POLYGON_SMOOTH);
  }
  initGlBlending();

  initialized_ = true;
}

void TestWidget::initGlBlending()
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDepthFunc(GL_NEVER);
  glDisable(GL_DEPTH_TEST);
}

void TestWidget::paintEvent(QPaintEvent* event)
{
  QPainter p(this);
  p.setRenderHints(QPainter::Antialiasing |
                   QPainter::TextAntialiasing |
                   QPainter::SmoothPixmapTransform |
                   QPainter::HighQualityAntialiasing,
                   enable_antialiasing_);
  p.beginNativePainting();
  // .beginNativePainting() disables blending and clears a handful of other
  // values that we need to manually reset.
  initGlBlending();
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  UpdateView();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Draw test pattern
  glLineWidth(3);
  glBegin(GL_LINES);
  // Red line to the right
  glColor3f(1, 0, 0);
  glVertex2f(0, 0);
  glVertex2f(20, 0);

  // Green line to the top
  glColor3f(0, 1, 0);
  glVertex2f(0, 0);
  glVertex2f(0, 20);
  glEnd();

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  p.endNativePainting();
}

void TestWidget::pushGlMatrices()
{
  glMatrixMode(GL_TEXTURE);
  glPushMatrix();
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glPushAttrib(GL_ALL_ATTRIB_BITS);
}

void TestWidget::popGlMatrices()
{
  glPopAttrib();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_TEXTURE);
  glPopMatrix();
}


void TestWidget::UpdateView()
{
  if (initialized_)
  {
    glViewport(0, 0, width(), height());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
  }
}

}

int main(int argc, char** argv)
{
  QApplication app(argc, argv);  
  QMainWindow win;
  test::TestWidget* widget = new test::TestWidget();
  win.setCentralWidget(widget);
  win.show();
  return app.exec();
}

