#ifndef QTEXTINLINEOBJECT
#define QTEXTINLINEOBJECT
class DummyQTextInlineObject {
//	Q_OBJECT;
public:
	knh_RawPtr_t *self;
	std::map<std::string, knh_Func_t *> *event_map;
	std::map<std::string, knh_Func_t *> *slot_map;
	DummyQTextInlineObject();
	void setSelf(knh_RawPtr_t *ptr);
	bool eventDispatcher(QEvent *event);
	bool addEvent(knh_Func_t *callback_func, std::string str);
	bool signalConnect(knh_Func_t *callback_func, std::string str);
	void connection(QObject *o);
};

class KQTextInlineObject : public QTextInlineObject {
//	Q_OBJECT;
public:
	knh_RawPtr_t *self;
	DummyQTextInlineObject *dummy;
	KQTextInlineObject(int i, QTextEngine* e);
	void setSelf(knh_RawPtr_t *ptr);
};

#endif //QTEXTINLINEOBJECT

