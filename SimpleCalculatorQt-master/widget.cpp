#include "widget.h"
#include "QDebug"
#include "QErrorMessage"

Widget::Widget(QWidget *parent) : QWidget(parent) {

  // initialize labels to define spin boxes
  QLabel *oper1 = new QLabel("value 1", this);
  QLabel *oper2 = new QLabel("value 2", this);
  QLabel *res = new QLabel("result", this);

  // Initialize default spin boxes
  m_spinFisrtOper = createDefaultSpinBox();
  m_spinSecOper = createDefaultSpinBox();
  m_spinResult = createDefaultSpinBox();

  // initialize evaluating buttons
  m_btnAdd = new QPushButton("Add", this);
  m_btnSubstract = new QPushButton("Substract", this);
  m_btnMultiply = new QPushButton("Multiply", this);
  m_btnDivide = new QPushButton("Divide", this);

  // initialize restore button
  m_btnRestore = new QPushButton("Restore result", this);
  m_resultHistory = QStack<double>();

  // set main layout
  setLayout(new QVBoxLayout());

  // Initialize default horizontal layouts
  QHBoxLayout *firstLay = createDefaultHorLayout(oper1, m_spinFisrtOper);
  QHBoxLayout *secLay = createDefaultHorLayout(oper2, m_spinSecOper);
  QHBoxLayout *resLay = createDefaultHorLayout(res, m_spinResult);

  // set layout of main evaulating buttons
  m_operationButtonHorizontalLayout = new QHBoxLayout;
  m_operationButtonHorizontalLayout->addWidget(m_btnAdd);
  m_operationButtonHorizontalLayout->addWidget(m_btnSubstract);
  m_operationButtonHorizontalLayout->addWidget(m_btnMultiply);
  m_operationButtonHorizontalLayout->addWidget(m_btnDivide);

  // add sublayouts into main layout
  layout()->addItem(firstLay);
  layout()->addItem(secLay);
  layout()->addItem(resLay);
  layout()->addItem(m_operationButtonHorizontalLayout);

  layout()->addWidget(m_btnRestore);

  // connect button's signal clicked with evaluating slot
  for (int i = 0; i < m_operationButtonHorizontalLayout->count(); ++i) {
    // cast and connect each button
    QPushButton *qBtn = qobject_cast<QPushButton *>(
        m_operationButtonHorizontalLayout->itemAt(i)->widget());
    if (qBtn)
      connect(qBtn, &QPushButton::clicked, this,
              &Widget::onOperationButtonClicked);
  }

  // connect to click restore button signal
  connect(m_btnRestore, &QPushButton::clicked, this,
          &::Widget::onRestoreButtonClicked);
}

Widget::~Widget() {}

// get double value from result spin box
double Widget::getResult() { return m_spinResult->value(); }

// creating spin boxes and defineing default settings of them
QDoubleSpinBox *Widget::createDefaultSpinBox() {
  QDoubleSpinBox *spinBox = new QDoubleSpinBox(this);
  spinBox->setDecimals(10);
  spinBox->setMaximum(std::numeric_limits<double>::max());
  spinBox->setMinimum(std::numeric_limits<double>::lowest());
  return spinBox;
}

// creating QHBoxLayout object and defineing default settings of it
QHBoxLayout *Widget::createDefaultHorLayout(QLabel *label,
                                            QDoubleSpinBox *spinBox) {
  QHBoxLayout *layout = new QHBoxLayout;
  layout->addWidget(label, 1);
  layout->addWidget(spinBox, 5);
  return layout;
}

// evaulate operation and set it in the resulting double spin box
void Widget::evaluate(int position) {
  switch (position) {
  case 0:
    m_spinResult->setValue(m_spinFisrtOper->value() + m_spinSecOper->value());
    break;
  case 1:
    m_spinResult->setValue(m_spinFisrtOper->value() - m_spinSecOper->value());
    break;
  case 2:
    m_spinResult->setValue(m_spinFisrtOper->value() * m_spinSecOper->value());
    break;
  case 3:
    if (m_spinSecOper->value() != 0)
      m_spinResult->setValue(m_spinFisrtOper->value() / m_spinSecOper->value());
    break;
  }
}

// find index of button in horizontal layout
int Widget::findButtonPostion(QPushButton *fBtn) {
  // find button
  for (int i = 0; i < m_operationButtonHorizontalLayout->count(); ++i) {
    QPushButton *temp = qobject_cast<QPushButton *>(
        m_operationButtonHorizontalLayout->itemAt(i)->widget());
    if (temp->text() == fBtn->text()) {
      return i;
    }
  }
  return -1;
}

void Widget::onOperationButtonClicked() {
  // cast sender
  QPushButton *btnOperation = qobject_cast<QPushButton *>(sender());
  if (btnOperation) {
    // get index of sender button
    int position = findButtonPostion(btnOperation);
    // get result
    evaluate(position);
    // save result
    m_resultHistory.push_back(m_spinResult->value());
  }
}

void Widget::onRestoreButtonClicked() {
  if (!m_resultHistory.empty()) {
    // get the last result
    m_spinResult->setValue(m_resultHistory.top());
    // delete the last result
    m_resultHistory.pop();
  }
}