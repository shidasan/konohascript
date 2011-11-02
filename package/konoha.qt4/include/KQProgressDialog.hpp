#ifndef QPROGRESSDIALOG
#define QPROGRESSDIALOG
class DummyQProgressDialog : public DummyQDialog {
	Q_OBJECT;
public:
	knh_RawPtr_t *self;
	std::map<std::string, knh_Func_t *> *event_map;
	std::map<std::string, knh_Func_t *> *slot_map;
	knh_Func_t *canceled_func;
	DummyQProgressDialog();
	void setSelf(knh_RawPtr_t *ptr);
	bool eventDispatcher(QEvent *event);
	bool addEvent(knh_Func_t *callback_func, std::string str);
	bool signalConnect(knh_Func_t *callback_func, std::string str);
	void connection(QObject *o);
public slots:
	bool canceledSlot();
};

class KQProgressDialog : public QProgressDialog {
//	Q_OBJECT;
public:
	knh_RawPtr_t *self;
	DummyQProgressDialog *dummy;
	KQProgressDialog(QWidget* parent, Qt::WindowFlags f);
	void setSelf(knh_RawPtr_t *ptr);
	bool event(QEvent *event);
};

#endif //QPROGRESSDIALOG

