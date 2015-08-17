/*=============================
	系统设置界面
=============================*/

#include "sys_set.h"
#include "define.h"
#include "sql/optMsg.h"
#include "sql/warnMsg.h"
#include "main.h"

#include <QColorDialog>
#include <QWidget>
#include <QMessageBox>
#include <QProcess>//20120727-modified
#include <termios.h> /* struct termios */
#include <unistd.h> /* usleep() */
SysSet::SysSet (IMFrame * im, QWidget * parent):QWidget (parent),
Ui_SysSetForm ()
{
  setupUi (this);
  imf = im;//QWSServer::setCurrentInputMethod(imf);
  setWindowFlags (Qt::Dialog);
  setGeometry (67, 80, 500, 340);
  setAttribute (Qt::WA_DeleteOnClose);	//关闭时自动的释放内存
  reset ();

  txtYear->installEventFilter (this);
  txtMonth->installEventFilter (this);
  txtDay->installEventFilter (this);
  txtHour->installEventFilter (this);
  txtMinute->installEventFilter (this);
  txtSec->installEventFilter (this);
  txtCSTime->installEventFilter (this);
  txtNet0->installEventFilter (this);
  txtNet1->installEventFilter (this);
  txtTimer->installEventFilter (this);
//  local_slave_address_txt->installEventFilter(this);

  usart1_badurate_comboBox->addItem("1200", BAUD1200);
  usart1_badurate_comboBox->addItem("2400", BAUD2400);
  usart1_badurate_comboBox->addItem("4800", BAUD4800);
  usart1_badurate_comboBox->addItem("9600", BAUD9600);
  usart1_badurate_comboBox->addItem("19200", BAUD19200);
  usart1_badurate_comboBox->addItem("38400", BAUD38400);
  usart1_badurate_comboBox->addItem("57600", BAUD57600);
  usart1_badurate_comboBox->addItem("115200", BAUD115200);
  usart1_badurate_comboBox->setCurrentIndex(3);
  usart1_parity_comboBox->addItem("无校验", PARITY_NONE);
  usart1_parity_comboBox->addItem("奇校验", PARITY_ODD);
  usart1_parity_comboBox->addItem("偶校验", PARITY_EVEN);
  usart1_parity_comboBox->setCurrentIndex(0);
  usart1_data_comboBox->addItem("8位", DATA_EIGHT);
  usart1_data_comboBox->addItem("7位", DATA_SEVEN);
  usart1_data_comboBox->addItem("6位", DATA_SIX);
  usart1_data_comboBox->setCurrentIndex(0);
  usart1_stop_comboBox->addItem("1位", STOP_ONE);
//  usart1_stop_comboBox->addItem("1.5位", STOP_ONE_FIVE);
  usart1_stop_comboBox->addItem("2位", STOP_TWO);
  usart1_stop_comboBox->setCurrentIndex(0);

  usart2_badurate_comboBox->addItem("1200", BAUD1200);
  usart2_badurate_comboBox->addItem("2400", BAUD2400);
  usart2_badurate_comboBox->addItem("4800", BAUD4800);
  usart2_badurate_comboBox->addItem("9600", BAUD9600);
  usart2_badurate_comboBox->addItem("19200", BAUD19200);
  usart2_badurate_comboBox->addItem("38400", BAUD38400);
  usart2_badurate_comboBox->addItem("57600", BAUD57600);
  usart2_badurate_comboBox->addItem("115200", BAUD115200);
  usart2_badurate_comboBox->setCurrentIndex(3);
  usart2_parity_comboBox->addItem("无校验", PARITY_NONE);
  usart2_parity_comboBox->addItem("奇校验", PARITY_ODD);
  usart2_parity_comboBox->addItem("偶校验", PARITY_EVEN);
  usart2_parity_comboBox->setCurrentIndex(0);
  usart2_data_comboBox->addItem("8位", DATA_EIGHT);
  usart2_data_comboBox->addItem("7位", DATA_SEVEN);
  usart2_data_comboBox->addItem("6位", DATA_SIX);
  usart2_data_comboBox->setCurrentIndex(0);
  usart2_stop_comboBox->addItem("1位", STOP_ONE);
 // usart2_stop_comboBox->addItem("1.5位", STOP_ONE_FIVE);
  usart2_stop_comboBox->addItem("2位", STOP_TWO);
  usart2_stop_comboBox->setCurrentIndex(0);

  usart3_badurate_comboBox->addItem("1200", BAUD1200);
  usart3_badurate_comboBox->addItem("2400", BAUD2400);
  usart3_badurate_comboBox->addItem("4800", BAUD4800);
  usart3_badurate_comboBox->addItem("9600", BAUD9600);
  usart3_badurate_comboBox->addItem("19200", BAUD19200);
  usart3_badurate_comboBox->addItem("38400", BAUD38400);
  usart3_badurate_comboBox->addItem("57600", BAUD57600);
  usart3_badurate_comboBox->addItem("115200", BAUD115200);
  usart3_badurate_comboBox->setCurrentIndex(3);
  usart3_parity_comboBox->addItem("无校验", PARITY_NONE);
  usart3_parity_comboBox->addItem("奇校验", PARITY_ODD);
  usart3_parity_comboBox->addItem("偶校验", PARITY_EVEN);
  usart3_parity_comboBox->setCurrentIndex(0);
  usart3_data_comboBox->addItem("8位", DATA_EIGHT);
  usart3_data_comboBox->addItem("7位", DATA_SEVEN);
  usart3_data_comboBox->addItem("6位", DATA_SIX);
  usart3_data_comboBox->setCurrentIndex(0);
  usart3_stop_comboBox->addItem("1位", STOP_ONE);
 // usart3_stop_comboBox->addItem("1.5位", STOP_ONE_FIVE);
  usart3_stop_comboBox->addItem("2位", STOP_TWO);
  usart3_stop_comboBox->setCurrentIndex(0);
  
  if (Can::open_flag == 1) {
    usart1_badurate_comboBox->setEnabled(false);
    usart1_parity_comboBox->setEnabled(false);
    usart1_data_comboBox->setEnabled(false);
    usart1_stop_comboBox->setEnabled(false);

    usart2_badurate_comboBox->setEnabled(false);
    usart2_parity_comboBox->setEnabled(false);
    usart2_data_comboBox->setEnabled(false);
    usart2_stop_comboBox->setEnabled(false);

    usart3_badurate_comboBox->setEnabled(false);
    usart3_parity_comboBox->setEnabled(false);
    usart3_data_comboBox->setEnabled(false);
    usart3_stop_comboBox->setEnabled(false);
    local_slave_address_txt->setEnabled(false);
    local_slave_address_txt->removeEventFilter(this);
  } else {
    usart1_badurate_comboBox->setEnabled(true);
    usart1_parity_comboBox->setEnabled(true);
    usart1_data_comboBox->setEnabled(true);
    usart1_stop_comboBox->setEnabled(true);

    usart2_badurate_comboBox->setEnabled(true);
    usart2_parity_comboBox->setEnabled(true);
    usart2_data_comboBox->setEnabled(true);
    usart2_stop_comboBox->setEnabled(true);

    usart3_badurate_comboBox->setEnabled(true);
    usart3_parity_comboBox->setEnabled(true);
    usart3_data_comboBox->setEnabled(true);
    usart3_stop_comboBox->setEnabled(true);
    local_slave_address_txt->setEnabled(true);
    local_slave_address_txt->installEventFilter(this);
  }

  connect (usart_btn_close, SIGNAL(clicked()), this, SLOT(usart_set()));
  connect (btn_reset, SIGNAL (clicked ()), this, SLOT (reset ()));
  connect (btn_ok, SIGNAL (clicked ()), this, SLOT (ok ()));
  connect (btn_clear_warn, SIGNAL (clicked ()), this, SLOT (clear_warn ()));
  connect (btn_clear_err, SIGNAL (clicked ()), this, SLOT (clear_err ()));
  connect (btn_clear_opt, SIGNAL (clicked ()), this, SLOT (clear_opt ()));
  connect (btn_calibration, SIGNAL (clicked()), this, SLOT (touch_calibration()));

  connect (txtCSTime, SIGNAL (textChanged (const QString)), this,
	   SLOT (txtChange (QString)));
  connect (txtYear, SIGNAL (textChanged (const QString)), this,
	   SLOT (txtChange (QString)));


  connect (btnSys1OK, SIGNAL (clicked ()), this, SLOT (set ()));
  connect (btnSys1Reset, SIGNAL (clicked ()), this, SLOT (resend ()));

  connect (txtMonth, SIGNAL (textChanged (const QString)), this,
	   SLOT (txtChange_ (QString)));
  connect (txtDay, SIGNAL (textChanged (const QString)), this,
	   SLOT (txtChange_ (QString)));
  connect (txtHour, SIGNAL (textChanged (const QString)), this,
	   SLOT (txtChange_ (QString)));
  connect (txtMinute, SIGNAL (textChanged (const QString)), this,
	   SLOT (txtChange_ (QString)));
  connect (txtSec, SIGNAL (textChanged (const QString)), this,
	   SLOT (txtChange_ (QString)));
//  connect (ts_pushButton, SIGNAL(clicked()),this, SLOT(on_pushbutton_clicked()));//20120727-modified

  printf ("init SysSet ok\n");
}

SysSet::~SysSet ()
{
  printf ("exit SysSet\n");
}

void
SysSet::_show ()
{
  if (Db::purview == DO)
    {
      btn_clear_warn->setEnabled (false);
      btn_clear_err->setEnabled (false);
      btn_clear_opt->setEnabled (false);
      btnSys1OK->setEnabled (false);
      usart_btn_close->setEnabled (false);
      usart1_badurate_comboBox->setEnabled(false);
      usart1_parity_comboBox->setEnabled(false);
      usart1_data_comboBox->setEnabled(false);
      usart1_stop_comboBox->setEnabled(false);

      usart2_badurate_comboBox->setEnabled(false);
      usart2_parity_comboBox->setEnabled(false);
      usart2_data_comboBox->setEnabled(false);
      usart2_stop_comboBox->setEnabled(false);

      usart3_badurate_comboBox->setEnabled(false);
      usart3_parity_comboBox->setEnabled(false);
      usart3_data_comboBox->setEnabled(false);
      usart3_stop_comboBox->setEnabled(false);
      local_slave_address_txt->setEnabled(false);
      local_slave_address_txt->removeEventFilter(this);
    }
  else
  {
      btn_clear_warn->setEnabled (true);
      btn_clear_err->setEnabled (true);
      btn_clear_opt->setEnabled (true);
      btnSys1OK->setEnabled (true);
      usart_btn_close->setEnabled (true);

      if (Can::open_flag == 1) {
        usart1_badurate_comboBox->setEnabled(false);
        usart1_parity_comboBox->setEnabled(false);
        usart1_data_comboBox->setEnabled(false);
        usart1_stop_comboBox->setEnabled(false);

        usart2_badurate_comboBox->setEnabled(false);
        usart2_parity_comboBox->setEnabled(false);
        usart2_data_comboBox->setEnabled(false);
        usart2_stop_comboBox->setEnabled(false);

        usart3_badurate_comboBox->setEnabled(false);
        usart3_parity_comboBox->setEnabled(false);
        usart3_data_comboBox->setEnabled(false);
        usart3_stop_comboBox->setEnabled(false);
        local_slave_address_txt->setEnabled(false);
        local_slave_address_txt->removeEventFilter(this);
    } else {
        usart1_badurate_comboBox->setEnabled(true);
        usart1_parity_comboBox->setEnabled(true);
        usart1_data_comboBox->setEnabled(true);
        usart1_stop_comboBox->setEnabled(true);

        usart2_badurate_comboBox->setEnabled(true);
        usart2_parity_comboBox->setEnabled(true);
        usart2_data_comboBox->setEnabled(true);
        usart2_stop_comboBox->setEnabled(true);

        usart3_badurate_comboBox->setEnabled(true);
        usart3_parity_comboBox->setEnabled(true);
        usart3_data_comboBox->setEnabled(true);
        usart3_stop_comboBox->setEnabled(true);
        local_slave_address_txt->setEnabled(true);
        local_slave_address_txt->installEventFilter(this);
    }

  }
  resend ();
}

void
SysSet::clear_warn ()
{
  if (QMessageBox::
      question (this, "提示信息", "真的要删除报警数据吗?",
		"确定", "取消") != 0)
    return;
  if (WarnMsg::delAll ())
    {
      OptMsg::insertClearWarnDat ();
      QMessageBox::question (this, "提示信息",
			     "报警数据记录清除成功！", "确定",
			     "取消");
    }
  else
    {
      QMessageBox::question (this, "提示信息",
			     "报警数据记录清除失败！", "确定",
			     "取消");
    }
  Db::vacuum ();
}

void
SysSet::clear_err ()
{
  if (QMessageBox::
      question (this, "提示信息", "真的要删除故障数据吗?",
        "确定", "取消") != 0)
    return;
  if (WarnMsg::delerrAll ())
    {
      OptMsg::insertClearErrDat ();
      QMessageBox::question (this, "提示信息",
                 "故障数据记录清除成功！", "确定",
                 "取消");
    }
  else
    {
      QMessageBox::question (this, "提示信息",
                 "故障数据记录清除失败！", "确定",
                 "取消");
    }
  Db::vacuum ();
}

void
SysSet::clear_opt ()
{
  if (QMessageBox::
      question (this, "提示信息", "真的要删除操作数据吗?",
		"确定", "取消") != 0)
    {
      return;
    }
  if (OptMsg::delAll ())
    {
      OptMsg::insertClearDoDat ();
      QMessageBox::question (this, "提示信息",
			     "操作数据记录清除成功！", "确定",
			     "取消");
    }
  else
    {
      QMessageBox::question (this, "提示信息",
			     "操作数据记录清除失败！", "确定",
			     "取消");
    }
  Db::vacuum ();
}

void
SysSet::touch_calibration()
{
  if (QMessageBox::
      question (this, "警告", "是否真的要重启设备,并重新校准屏幕?",
                "确定", "取消") != 0)
    {
      return;
    }
  ::system("rm -rf /etc/pointercal");
  ::system("reboot");
}


// 设置系统参数
void
SysSet::set ()
{
  if ((txtNet0->text().toInt() > 128) || (txtNet1->text().toInt() > 128)) {
    QMessageBox::information(this, tr("输入错误"), tr("最多128节点."), tr("确定"));
    return;
  }
  if (txtTimer->text().toInt() > 5) {
    QMessageBox::information(this, tr("输入错误"), tr("重发最多5次."), tr("确定"));
    return;
  }
  if ((local_slave_address_txt->text().toInt() < 1) || (local_slave_address_txt->text().toInt() > 247)) {
    QMessageBox::information(this, tr("输入错误"), tr("正确地址范围为1——247."), tr("确定"));
    return;
  }
  if (Mater::writeNet0Count (txtNet0->text ()) &&
      Mater::writeNet1Count (txtNet1->text ()) &&
      Mater::writeSendTimer (txtTimer->text ()))
    {
      if (Can::open_flag == 0) {
        usart1_set(usart1_badurate_comboBox->currentText(), usart1_parity_comboBox->currentText(),
        usart1_data_comboBox->currentText(), usart1_stop_comboBox->currentText());

        usart2_set(usart2_badurate_comboBox->currentText(), usart2_parity_comboBox->currentText(),
        usart2_data_comboBox->currentText(), usart2_stop_comboBox->currentText());

        usart3_set(usart3_badurate_comboBox->currentText(), usart3_parity_comboBox->currentText(),
        usart3_data_comboBox->currentText(), usart3_stop_comboBox->currentText());

	Mater::writeLocalAddress(local_slave_address_txt->text());	

        Can::init();
	SysSet::_show();
      }
      QMessageBox::question (this, "提示信息", "设置成功！",
			     "确定", "取消");
    }
  else
    {
      QMessageBox::question (this, "提示信息", "设置失败！",
			     "确定", "取消");
    }
}

void SysSet::usart_reset(QComboBox *usart, const QString &text)
{
  if (usart != NULL) {
    if (text == "1200") {
      usart->setCurrentIndex(0);
    } else if (text == "2400") {
      usart->setCurrentIndex(1);
    } else if (text == "4800") {
      usart->setCurrentIndex(2);
    } else if (text == "9600") {
      usart->setCurrentIndex(3);
    } else if (text == "19200") {
      usart->setCurrentIndex(4);
    } else if (text == "38400") {
      usart->setCurrentIndex(5);
    } else if (text == "57600") {
      usart->setCurrentIndex(6);
    } else if (text == "115200") {
      usart->setCurrentIndex(7);
    } else if (text == "无校验") {
      usart->setCurrentIndex(0);
    } else if (text == "奇校验") {
      usart->setCurrentIndex(1);
    } else if (text == "偶校验") {
      usart->setCurrentIndex(2);
    } else if (text == "8位") {
      usart->setCurrentIndex(0);
    } else if (text == "7位") {
      usart->setCurrentIndex(1);
    } else if (text == "6位") {
      usart->setCurrentIndex(2);
    } else if (text == "1位") {
      usart->setCurrentIndex(0);
 /*   } else if (text == "1.5位") {
      usart->setCurrentIndex(1);*/
    } else if (text == "2位") {
      usart->setCurrentIndex(1);
    }
  }
}

void SysSet::usart1_reset(const QString &baudrate, const QString &parity, const QString &data, const QString &stop)
{
  usart_reset(usart1_badurate_comboBox, baudrate);
  usart_reset(usart1_parity_comboBox, parity);
  usart_reset(usart1_data_comboBox, data);
  usart_reset(usart1_stop_comboBox, stop);
}

void SysSet::usart2_reset(const QString &baudrate, const QString &parity, const QString &data, const QString &stop)
{
  usart_reset(usart2_badurate_comboBox, baudrate);
  usart_reset(usart2_parity_comboBox, parity);
  usart_reset(usart2_data_comboBox, data);
  usart_reset(usart2_stop_comboBox, stop);
}

void SysSet::usart3_reset(const QString &baudrate, const QString &parity, const QString &data, const QString &stop)
{
  usart_reset(usart3_badurate_comboBox, baudrate);
  usart_reset(usart3_parity_comboBox, parity);
  usart_reset(usart3_data_comboBox, data);
  usart_reset(usart3_stop_comboBox, stop);
}

// 读取系统参数
void
SysSet::resend ()
{
  txtNet0->setText (QString::number (Mater::readNet0Count ()));
  //txtNet0->setText (QString::number (128));//debug zhq
  txtNet1->setText (QString::number (Mater::readNet1Count ()));
  txtTimer->setText (QString::number (Mater::readSendTimer ()));
  local_slave_address_txt->setText(QString::number(Mater::readLocalAddress()));
  usart1_reset(Mater::readUsart1Baudrate(), Mater::readUsart1Parity(),
    Mater::readUsart1Data(), Mater::readUsart1Stop());
  usart2_reset(Mater::readUsart2Baudrate(), Mater::readUsart2Parity(),
    Mater::readUsart2Data(), Mater::readUsart2Stop());
  usart3_reset(Mater::readUsart3Baudrate(), Mater::readUsart3Parity(),
    Mater::readUsart3Data(), Mater::readUsart3Stop());
}

void SysSet::usart_set()
{
  if (Can::open_flag == 1) {
    Can::fd_close();
  } 
  usart1_badurate_comboBox->setEnabled(true);
  usart1_parity_comboBox->setEnabled(true);
  usart1_data_comboBox->setEnabled(true);
  usart1_stop_comboBox->setEnabled(true);
  
  usart2_badurate_comboBox->setEnabled(true);
  usart2_parity_comboBox->setEnabled(true);
  usart2_data_comboBox->setEnabled(true);
  usart2_stop_comboBox->setEnabled(true);

  usart3_badurate_comboBox->setEnabled(true);
  usart3_parity_comboBox->setEnabled(true);
  usart3_data_comboBox->setEnabled(true);
  usart3_stop_comboBox->setEnabled(true);
  local_slave_address_txt->setEnabled(true);
  local_slave_address_txt->installEventFilter(this);
}

void SysSet::usart_set_common(QComboBox *usart, const QString &text)
{
	if ((text == "1200") || (text == "2400") || (text == "4800") 
	|| (text == "9600") || (text == "19200") || (text == "38400")
	|| (text == "57600") || (text == "115200")) {
		if (usart == usart1_badurate_comboBox) {
			Mater::writeUsart1Baudrate(text);
		} else if (usart == usart2_badurate_comboBox) {
			Mater::writeUsart2Baudrate(text);
		} else if (usart == usart3_badurate_comboBox) {
			Mater::writeUsart3Baudrate(text);
		}
	} else if ((text == "无校验") || (text == "奇校验") || (text == "偶校验")) {
		if (usart == usart1_parity_comboBox) {
			Mater::writeUsart1Parity(text);
		} else if (usart == usart2_parity_comboBox) {
			Mater::writeUsart2Parity(text);
		} else if (usart == usart3_parity_comboBox) {
			Mater::writeUsart3Parity(text);
		}
	} else if ((text == "8位") || (text == "7位") || (text == "6位")) {
		if (usart == usart1_data_comboBox) {
			Mater::writeUsart1Data(text);
		} else if (usart == usart2_data_comboBox) {
			Mater::writeUsart2Data(text);
		} else if (usart == usart3_data_comboBox) {
			Mater::writeUsart3Data(text);
		}
	} else if ((text == "1位") /*|| (text == "1.5位") */|| (text == "2位")) {
		if (usart == usart1_stop_comboBox) {
			Mater::writeUsart1Stop(text);
		} else if (usart == usart2_stop_comboBox) {
			Mater::writeUsart2Stop(text);
		} else if (usart == usart3_stop_comboBox) {
			Mater::writeUsart3Stop(text);
		}
	}
}

void SysSet::usart1_set(const QString &baudrate, const QString &parity, const QString &data, const QString &stop)
{
	usart_set_common(usart1_badurate_comboBox, baudrate);
	usart_set_common(usart1_parity_comboBox, parity);
	usart_set_common(usart1_data_comboBox, data);
	usart_set_common(usart1_stop_comboBox, stop);
}

void SysSet::usart2_set(const QString &baudrate, const QString &parity, const QString &data, const QString &stop)
{
	usart_set_common(usart2_badurate_comboBox, baudrate);
	usart_set_common(usart2_parity_comboBox, parity);
	usart_set_common(usart2_data_comboBox, data);
	usart_set_common(usart2_stop_comboBox, stop);
}

void SysSet::usart3_set(const QString &baudrate, const QString &parity, const QString &data, const QString &stop)
{
	usart_set_common(usart3_badurate_comboBox, baudrate);
	usart_set_common(usart3_parity_comboBox, parity);
	usart_set_common(usart3_data_comboBox, data);
	usart_set_common(usart3_stop_comboBox, stop);
}

//============ 重置 ============
void
SysSet::reset ()
{
  txtCSTime->setText (QString::number (Mater::read ()));
  initSystime ();
}

//===================确定修改================
void
SysSet::ok ()
{
  if (Mater::write (txtCSTime->text ()))
    {
      Main::screenWaitTime = txtCSTime->text ().toInt () * 60 * 1000;
      QMessageBox::question (this, tr ("提示信息"),
			     tr ("屏幕等待时间修改成功了！"),
			     tr ("确定"), tr ("取消"));
    }
  else
    {
      QMessageBox::question (this, tr ("提示信息"),
			     tr ("屏幕等待时间修改失败了！"),
			     tr ("确定"), tr ("取消"));
    }
  setSysTime ();
}

void
SysSet::initSystime ()
{
  time_t t;
  struct tm *p;
  tzset ();
  memset (&t, 0, sizeof (t));
  time (&t);
  p = localtime (&t);

  txtYear->setText (QString::number (1900 + p->tm_year));
  txtMonth->setText (QString::number (1 + p->tm_mon));
  txtDay->setText (QString::number (p->tm_mday));
  txtHour->setText (QString::number (p->tm_hour));
  txtMinute->setText (QString::number (p->tm_min));
  txtSec->setText (QString::number (p->tm_sec));
}

bool
SysSet::eventFilter (QObject * obj, QEvent * event)
{
  QLineEdit *txt = (QLineEdit *) obj;
  QWidget *wid = (QWidget *) obj;
  QRect qr, qr1;
  if (event->type () == QEvent::MouseButtonPress)
    {
      qr = wid->geometry ();
      int w = qr.width ();
      int h = qr.height ();
      wid = wid->parentWidget ();
      while (wid != 0)
	{
	  qr1 = wid->geometry ();
	  qr.setX (qr.x () + qr1.x ());
	  qr.setY (qr.y () + qr1.y ());
	  wid = wid->parentWidget ();
	}
      qr.setRect (qr.x (), qr.y (), w, h);
      imf->my_show (&qr, txt);
    }
  if (event->type () == QEvent::FocusOut)
    {
      imf->my_hide ();
    }
  return QWidget::eventFilter (obj, event);
}

bool
SysSet::isAbigB (struct tm * a, struct tm * b)
{
  bool ret = false;
  if (a->tm_year > b->tm_year)
    {
      ret = true;
    }
  else if (a->tm_year == b->tm_year)
    {
      if (a->tm_mon > b->tm_mon)
	{
	  ret = true;
	}
      else if (a->tm_mon == b->tm_mon)
	{
	  if (a->tm_mday > b->tm_mday)
	    {
	      ret = true;
	    }
	  else if (a->tm_mday == b->tm_mday)
	    {
	      if (a->tm_hour > b->tm_hour)
		{
		  ret = true;
		}
	      else if (a->tm_hour == b->tm_hour)
		{
		  if (a->tm_min > b->tm_min)
		    {
		      ret = true;
		    }
		  else if (a->tm_min == b->tm_min)
		    {
		      if (a->tm_sec > b->tm_sec)
			{
			  ret = true;
			}
		    }
		}
	    }
	}
    }
  return ret;
}

//====================写下系统时间====================
void
SysSet::setSysTime ()
{
  int flag = 0;
  time_t t1;
  struct tm *p1, tm1;
  tzset ();
  time (&t1);
  p1 = localtime (&t1);
  memcpy (&tm1, p1, sizeof (tm1));

  time_t t;
  struct tm *p;
  struct timeval tv;
  struct timezone tz;
  tz.tz_minuteswest = 0;
  tz.tz_dsttime = 0;
  time (&t);
  p = gmtime (&t);
  p->tm_year = txtYear->text ().toInt () - 1900;
  p->tm_mon = txtMonth->text ().toInt () - 1;
  p->tm_mday = txtDay->text ().toInt ();
  p->tm_hour = txtHour->text ().toInt ();
  p->tm_min = txtMinute->text ().toInt ();
  p->tm_sec = txtSec->text ().toInt ();

  if (isAbigB (&tm1, p))
    {
      if (QMessageBox::
	  question (this, tr ("提示信息"),
		    tr
		    ("修改的时间比当前时间小需要重启,确定修改吗？"),
		    tr ("确定"), tr ("取消")) != 0)
	return;
      else
	flag = 1;
    }
  t = mktime (p);
  tv.tv_sec = t;
  tv.tv_usec = 0;
  if (settimeofday (&tv, &tz) < 0)
    QMessageBox::question (this, tr ("提示信息"),
			   tr ("时间修改失败！"), tr ("确定"),
			   tr ("取消"));
  else
    {
      ::system ("hwclock -w");
      OptMsg::insertSysTimeSet ();
      QMessageBox::question (this, tr ("提示信息"),
			     tr ("时间修改成功!"), tr ("确定"),
			     tr ("取消"));
      if (flag == 1)
	::system ("reboot");
    }
}

/*============================*/
// 控制字符串的长度
void
SysSet::txtChange (const QString & str)
{
  QLineEdit *txt = qobject_cast < QLineEdit * >(sender ());
  if (str.length () > 4)
    txt->setText (str.left (4));
}

/*============================*/
// 控制字符串的长度
void
SysSet::txtChange_ (const QString & str)
{
  QLineEdit *txt = qobject_cast < QLineEdit * >(sender ());
  if (str.length () > 2)
    txt->setText (str.left (2));
}

void SysSet::usart_config_common(int fd, const QString &baudrate, const QString &parity, const QString &data, const QString &stop)
{
	struct termios newtio;
	static unsigned int RS485Baud = B9600;
	
	if (fd < 0)
		return;
		
	/* clear struct for new port settings */
	bzero(&newtio, sizeof(newtio));
	
	if (baudrate == "1200") {
		RS485Baud = B1200;
	} else if (baudrate == "2400") {
		RS485Baud = B2400;
	} else if (baudrate == "4800") {
		RS485Baud = B4800;
	} else if (baudrate == "9600") {
		RS485Baud = B9600;
	} else if (baudrate == "19200") {
		RS485Baud = B19200;
	} else if (baudrate == "38400") {
		RS485Baud = B38400;
	} else if (baudrate == "57600") {
		RS485Baud = B57600;
	} else if (baudrate == "115200") {
		RS485Baud = B115200;
	}
	
	newtio.c_cflag = RS485Baud | CLOCAL | CREAD;
	newtio.c_cflag &= ~CRTSCTS;
	
	if (data == "6位") {
		newtio.c_cflag |= CS6;
	} else if (data == "7位") {
		newtio.c_cflag |= CS7;
	} else if(data == "8位") {
		newtio.c_cflag |= CS8;
	}
	
	if (parity == "无校验") {
		newtio.c_cflag &= ~PARENB;
	} else if (parity == "奇校验") {
		newtio.c_cflag |= (PARENB | PARODD);
	} else if (parity == "偶校验") {
		newtio.c_cflag |= PARENB;
		newtio.c_cflag &= ~PARODD;
	}
	
	if (stop == "1位") {
		newtio.c_cflag &= ~CSTOPB;
	} else if (stop == "2位") {
		newtio.c_cflag |= CSTOPB;
	}
	
	/* Raw input */
	newtio.c_iflag = 0;
	/* Raw output */
	newtio.c_oflag = 0;
	/* no processing */
	newtio.c_lflag = 0;
	/* activate the settings for the port after flushing I/O */
	tcsetattr(fd, TCSAFLUSH, &newtio);
	/* flush any data waiting */
	usleep(200000);
	tcflush(fd, TCIOFLUSH);
	qDebug("usart configuration succeeded!\n");
}

void SysSet::usart1_config(int fd)
{
	SysSet::usart_config_common(fd, Mater::readUsart1Baudrate(), Mater::readUsart1Parity(),
	Mater::readUsart1Data(), Mater::readUsart1Stop());
}

void SysSet::usart2_config(int fd)
{
	SysSet::usart_config_common(fd, Mater::readUsart2Baudrate(), Mater::readUsart2Parity(),
	Mater::readUsart2Data(), Mater::readUsart2Stop());
}

void SysSet::usart3_config(int fd)
{
	SysSet::usart_config_common(fd, Mater::readUsart3Baudrate(), Mater::readUsart3Parity(),
	Mater::readUsart3Data(), Mater::readUsart3Stop());
}


/*============================*/
//触摸屏校准
/*void SysSet::on_pushbutton_clicked()
{
	QProcess *pro = new QProcess;
	pro->start("/bin/ts_calibrate -qws");
}*/
