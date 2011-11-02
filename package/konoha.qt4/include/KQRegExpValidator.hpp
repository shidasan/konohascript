#ifndef QREGEXPVALIDATOR
#define QREGEXPVALIDATOR
class DummyQRegExpValidator : public DummyQValidator {
//	Q_OBJECT;
public:
	knh_RawPtr_t *self;
	std::map<std::string, knh_Func_t *> *event_map;
	std::map<std::string, knh_Func_t *> *slot_map;
	DummyQRegExpValidator();
	void setSelf(knh_RawPtr_t *ptr);
	bool eventDispatcher(QEvent *event);
	bool addEvent(knh_Func_t *callback_func, std::string str);
	bool signalConnect(knh_Func_t *callback_func, std::string str);
	void connection(QObject *o);
};

class KQRegExpValidator : public QRegExpValidator {
//	Q_OBJECT;
public:
	knh_RawPtr_t *self;
	DummyQRegExpValidator *dummy;
	KQRegExpValidator(QObject* parent);
	void setSelf(knh_RawPtr_t *ptr);
	bool event(QEvent *event);
};

#endif //QREGEXPVALIDATOR

