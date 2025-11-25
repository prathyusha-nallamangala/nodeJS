#ifndef WIDGET_H
#define WIDGET_H

#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStack>
#include <QVBoxLayout>
#include <QWidget>

class Widget : public QWidget {
  Q_OBJECT

  QLabel *oper1;
  QLabel *oper2;
  QLabel *res;

  QDoubleSpinBox *m_spinFisrtOper; // first operand
  QDoubleSpinBox *m_spinSecOper;   // second operand

  QDoubleSpinBox *m_spinResult; // result of math operation

  QPushButton *m_btnAdd;       // button '+'
  QPushButton *m_btnSubstract; // button '-'
  QPushButton *m_btnMultiply;  // button '*'
  QPushButton *m_btnDivide;    // button '/'

  QPushButton *m_btnRestore; // button 'Restore results'
  // stack to manipulate previous results
  QStack<double> m_resultHistory;

  QHBoxLayout *m_operationButtonHorizontalLayout;

  QDoubleSpinBox *createDefaultSpinBox();
  QHBoxLayout *createDefaultHorLayout(QLabel *label, QDoubleSpinBox *spinBox);
  void evaluate(int position);
  int findButtonPostion(QPushButton *);
public slots:
  void onOperationButtonClicked();
  void onRestoreButtonClicked();

public:
  Widget(QWidget *parent = nullptr);
  ~Widget();
  double getResult();
  void setLay(QHBoxLayout *newLay);
};
#endif // WIDGET_H