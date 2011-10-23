#ifndef QSIGNALMAPPER
#define QSIGNALMAPPER
class DummyQSignalMapper : public DummyQObject {
//	Q_OBJECT;
public:
	knh_RawPtr_t *self;
	std::map<std::string, knh_Func_t *> *event_map;
	std::map<std::string, knh_Func_t *> *slot_map;
	DummyQSignalMapper();
	void setSelf(knh_RawPtr_t *ptr);
	bool eventDispatcher(QEvent *event);
	bool addEvent(knh_Func_t *callback_func, std::string str);
	bool signalConnect(knh_Func_t *callback_func, std::string str);
	void connection(QObject *o);
};

class KQSignalMapper : public QSignalMapper {
//	Q_OBJECT;
public:
	knh_RawPtr_t *self;
	DummyQSignalMapper *dummy;
	KQSignalMapper(QObject* parent);
	void setSelf(knh_RawPtr_t *ptr);
	bool event(QEvent *event);
};

#endif //QSIGNALMAPPER

