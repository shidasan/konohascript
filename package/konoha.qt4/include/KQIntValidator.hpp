#ifndef QINTVALIDATOR
#define QINTVALIDATOR
class DummyQIntValidator : public DummyQValidator {
//	Q_OBJECT;
public:
	knh_RawPtr_t *self;
	std::map<std::string, knh_Func_t *> *event_map;
	std::map<std::string, knh_Func_t *> *slot_map;
	DummyQIntValidator();
	void setSelf(knh_RawPtr_t *ptr);
	bool eventDispatcher(QEvent *event);
	bool addEvent(knh_Func_t *callback_func, std::string str);
	bool signalConnect(knh_Func_t *callback_func, std::string str);
	void connection(QObject *o);
};

class KQIntValidator : public QIntValidator {
//	Q_OBJECT;
public:
	knh_RawPtr_t *self;
	DummyQIntValidator *dummy;
	KQIntValidator(QObject* parent);
	void setSelf(knh_RawPtr_t *ptr);
	bool event(QEvent *event);
};

#endif //QINTVALIDATOR

