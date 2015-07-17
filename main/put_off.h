/*==============================================
	 脱扣界面
==============================================*/
#ifndef LINLONG_PutOff
#define LINLONG_PutOff
#include "ui_put_off.h"
#include "rxdata.h"
#include "signals.h"
#include "module/modList.h"
#include "sql/warnMsg.h"
#include <QMessageBox>
#include <QString>

class  PutOff:public QWidget,public Ui_PutOffForm
{
        Q_OBJECT
public :
        PutOff(Signals *p_rx,QWidget* parent = NULL);
        virtual ~PutOff();
	void _show();
private:
	virtual void closeEvent ( QCloseEvent * event );
public slots:
	void ok();
	void currentTextCh(const QString & text);
public:
	void getOk(int i);
};
#endif
