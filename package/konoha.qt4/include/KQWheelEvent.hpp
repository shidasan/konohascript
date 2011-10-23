#ifndef QWHEELEVENT
#define QWHEELEVENT
class DummyQWheelEvent : public DummyQInputEvent {
//	Q_OBJECT;
public:
	knh_RawPtr_t *self;
	std::map<std::string, knh_Func_t *> *event_map;
	std::map<std::string, knh_Func_t *> *slot_map;
	DummyQWheelEvent();
	void setSelf(knh_RawPtr_t *ptr);
	bool eventDispatcher(QEvent *event);
	bool addEvent(knh_Func_t *callback_func, std::string str);
	bool signalConnect(knh_Func_t *callback_func, std::string str);
	void connection(QObject *o);
};

class KQWheelEvent : public QWheelEvent {
//	Q_OBJECT;
public:
	knh_RawPtr_t *self;
	DummyQWheelEvent *dummy;
	KQWheelEvent(const QPoint pos, int delta, Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers, Qt::Orientation orient);
	void setSelf(knh_RawPtr_t *ptr);
};

#endif //QWHEELEVENT

