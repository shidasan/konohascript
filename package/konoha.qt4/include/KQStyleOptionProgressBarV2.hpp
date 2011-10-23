#ifndef QSTYLEOPTIONPROGRESSBARV2
#define QSTYLEOPTIONPROGRESSBARV2
class DummyQStyleOptionProgressBarV2 : public DummyQStyleOptionProgressBar {
//	Q_OBJECT;
public:
	knh_RawPtr_t *self;
	std::map<std::string, knh_Func_t *> *event_map;
	std::map<std::string, knh_Func_t *> *slot_map;
	DummyQStyleOptionProgressBarV2();
	void setSelf(knh_RawPtr_t *ptr);
	bool eventDispatcher(QEvent *event);
	bool addEvent(knh_Func_t *callback_func, std::string str);
	bool signalConnect(knh_Func_t *callback_func, std::string str);
	void connection(QObject *o);
};

class KQStyleOptionProgressBarV2 : public QStyleOptionProgressBarV2 {
//	Q_OBJECT;
public:
	knh_RawPtr_t *self;
	DummyQStyleOptionProgressBarV2 *dummy;
	KQStyleOptionProgressBarV2();
	void setSelf(knh_RawPtr_t *ptr);
};

#endif //QSTYLEOPTIONPROGRESSBARV2

