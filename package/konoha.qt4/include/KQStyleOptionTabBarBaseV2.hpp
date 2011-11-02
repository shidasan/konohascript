#ifndef QSTYLEOPTIONTABBARBASEV2
#define QSTYLEOPTIONTABBARBASEV2
class DummyQStyleOptionTabBarBaseV2 : public DummyQStyleOptionTabBarBase {
//	Q_OBJECT;
public:
	knh_RawPtr_t *self;
	std::map<std::string, knh_Func_t *> *event_map;
	std::map<std::string, knh_Func_t *> *slot_map;
	DummyQStyleOptionTabBarBaseV2();
	void setSelf(knh_RawPtr_t *ptr);
	bool eventDispatcher(QEvent *event);
	bool addEvent(knh_Func_t *callback_func, std::string str);
	bool signalConnect(knh_Func_t *callback_func, std::string str);
	void connection(QObject *o);
};

class KQStyleOptionTabBarBaseV2 : public QStyleOptionTabBarBaseV2 {
//	Q_OBJECT;
public:
	knh_RawPtr_t *self;
	DummyQStyleOptionTabBarBaseV2 *dummy;
	KQStyleOptionTabBarBaseV2();
	void setSelf(knh_RawPtr_t *ptr);
};

#endif //QSTYLEOPTIONTABBARBASEV2

