#ifndef A1_MAZE_1_CONTROL_WIDGET_H_
#define A1_MAZE_1_CONTROL_WIDGET_H_

#include <QFileDialog>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Control;
}
QT_END_NAMESPACE

namespace s21 {
class Control : public QWidget {
  Q_OBJECT

 public:
  Control(QWidget *parent = nullptr);
  ~Control();

  int GetRow();
  int GetCol();
  int GetStartX();
  int GetStartY();
  int GetEndX();
  int GetEndY();
  void SetMaxValuePathSpinbox(const int &rows, const int &cols);
  void SetTextOfMazeSize(const int &rows, const int &cols);
  void SetTextOfFileName(QString file_path);

 public slots:
  void OpenFile();
  void SaveFile();

 signals:
  void GenerateMazeClicked();
  void FindPathClicked();
  void OpenFileClicked(const QString &file_path);
  void SaveFileClicked(const QString &file_path);

 private:
  void Connections();

  Ui::Control *ui_;
};
}  // namespace s21
#endif  // A1_MAZE_1_CONTROL_WIDGET_H_
