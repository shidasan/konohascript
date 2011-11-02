#ifndef QTREEWIDGETITEM
#define QTREEWIDGETITEM
class DummyQTreeWidgetItem {
//	Q_OBJECT;
public:
	knh_RawPtr_t *self;
	std::map<std::string, knh_Func_t *> *event_map;
	std::map<std::string, knh_Func_t *> *slot_map;
	DummyQTreeWidgetItem();
	void setSelf(knh_RawPtr_t *ptr);
	bool eventDispatcher(QEvent *event);
	bool addEvent(knh_Func_t *callback_func, std::string str);
	bool signalConnect(knh_Func_t *callback_func, std::string str);
	void connection(QObject *o);
};

class KQTreeWidgetItem : public QTreeWidgetItem {
//	Q_OBJECT;
public:
	knh_RawPtr_t *self;
	DummyQTreeWidgetItem *dummy;
	KQTreeWidgetItem(int type);
	void setSelf(knh_RawPtr_t *ptr);
};

#endif //QTREEWIDGETITEM

