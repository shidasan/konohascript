#ifndef QTRANSFORM
#define QTRANSFORM
class DummyQTransform {
//	Q_OBJECT;
public:
	knh_RawPtr_t *self;
	std::map<std::string, knh_Func_t *> *event_map;
	std::map<std::string, knh_Func_t *> *slot_map;
	DummyQTransform();
	void setSelf(knh_RawPtr_t *ptr);
	bool eventDispatcher(QEvent *event);
	bool addEvent(knh_Func_t *callback_func, std::string str);
	bool signalConnect(knh_Func_t *callback_func, std::string str);
	void connection(QObject *o);
};

class KQTransform : public QTransform {
//	Q_OBJECT;
public:
	knh_RawPtr_t *self;
	DummyQTransform *dummy;
	KQTransform();
	void setSelf(knh_RawPtr_t *ptr);
};

#endif //QTRANSFORM

