//@Virtual @Override QSize QAbstractScrollArea.minimumSizeHint();
KMETHOD QAbstractScrollArea_minimumSizeHint(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QAbstractScrollArea *  qp = RawPtr_to(QAbstractScrollArea *, sfp[0]);
	if (qp) {
		QSize ret_v = qp->minimumSizeHint();
		QSize *ret_v_ = new QSize(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//@Virtual @Override QSize QAbstractScrollArea.sizeHint();
KMETHOD QAbstractScrollArea_sizeHint(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QAbstractScrollArea *  qp = RawPtr_to(QAbstractScrollArea *, sfp[0]);
	if (qp) {
		QSize ret_v = qp->sizeHint();
		QSize *ret_v_ = new QSize(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//
//void QAbstractScrollArea.addScrollBarWidget(QWidget widget, QtAlignment alignment);
KMETHOD QAbstractScrollArea_addScrollBarWidget(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QAbstractScrollArea *  qp = RawPtr_to(QAbstractScrollArea *, sfp[0]);
	if (qp) {
		QWidget*  widget = RawPtr_to(QWidget*, sfp[1]);
		initFlag(alignment, Qt::Alignment, sfp[2]);
		qp->addScrollBarWidget(widget, alignment);
	}
	RETURNvoid_();
}

//QWidget QAbstractScrollArea.getCornerWidget();
KMETHOD QAbstractScrollArea_getCornerWidget(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QAbstractScrollArea *  qp = RawPtr_to(QAbstractScrollArea *, sfp[0]);
	if (qp) {
		QWidget* ret_v = qp->cornerWidget();
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, (QWidget*)ret_v, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//QScrollBar QAbstractScrollArea.getHorizontalScrollBar();
KMETHOD QAbstractScrollArea_getHorizontalScrollBar(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QAbstractScrollArea *  qp = RawPtr_to(QAbstractScrollArea *, sfp[0]);
	if (qp) {
		QScrollBar* ret_v = qp->horizontalScrollBar();
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, (QScrollBar*)ret_v, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//int QAbstractScrollArea.getHorizontalScrollBarPolicy();
KMETHOD QAbstractScrollArea_getHorizontalScrollBarPolicy(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QAbstractScrollArea *  qp = RawPtr_to(QAbstractScrollArea *, sfp[0]);
	if (qp) {
		Qt::ScrollBarPolicy ret_v = qp->horizontalScrollBarPolicy();
		RETURNi_(ret_v);
	} else {
		RETURNi_(0);
	}
}

//QSize QAbstractScrollArea.maximumViewportSize();
KMETHOD QAbstractScrollArea_maximumViewportSize(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QAbstractScrollArea *  qp = RawPtr_to(QAbstractScrollArea *, sfp[0]);
	if (qp) {
		QSize ret_v = qp->maximumViewportSize();
		QSize *ret_v_ = new QSize(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//QWidgetList QAbstractScrollArea.scrollBarWidgets(QtAlignment alignment);
KMETHOD QAbstractScrollArea_scrollBarWidgets(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QAbstractScrollArea *  qp = RawPtr_to(QAbstractScrollArea *, sfp[0]);
	if (qp) {
		initFlag(alignment, Qt::Alignment, sfp[1]);
		QWidgetList ret_v = qp->scrollBarWidgets(alignment);
		QWidgetList *ret_v_ = new QWidgetList(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//void QAbstractScrollArea.setCornerWidget(QWidget widget);
KMETHOD QAbstractScrollArea_setCornerWidget(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QAbstractScrollArea *  qp = RawPtr_to(QAbstractScrollArea *, sfp[0]);
	if (qp) {
		QWidget*  widget = RawPtr_to(QWidget*, sfp[1]);
		qp->setCornerWidget(widget);
	}
	RETURNvoid_();
}

//void QAbstractScrollArea.setHorizontalScrollBar(QScrollBar scrollBar);
KMETHOD QAbstractScrollArea_setHorizontalScrollBar(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QAbstractScrollArea *  qp = RawPtr_to(QAbstractScrollArea *, sfp[0]);
	if (qp) {
		QScrollBar*  scrollBar = RawPtr_to(QScrollBar*, sfp[1]);
		qp->setHorizontalScrollBar(scrollBar);
	}
	RETURNvoid_();
}

//void QAbstractScrollArea.setHorizontalScrollBarPolicy(int arg0);
KMETHOD QAbstractScrollArea_setHorizontalScrollBarPolicy(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QAbstractScrollArea *  qp = RawPtr_to(QAbstractScrollArea *, sfp[0]);
	if (qp) {
		Qt::ScrollBarPolicy arg0 = Int_to(Qt::ScrollBarPolicy, sfp[1]);
		qp->setHorizontalScrollBarPolicy(arg0);
	}
	RETURNvoid_();
}

//void QAbstractScrollArea.setVerticalScrollBar(QScrollBar scrollBar);
KMETHOD QAbstractScrollArea_setVerticalScrollBar(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QAbstractScrollArea *  qp = RawPtr_to(QAbstractScrollArea *, sfp[0]);
	if (qp) {
		QScrollBar*  scrollBar = RawPtr_to(QScrollBar*, sfp[1]);
		qp->setVerticalScrollBar(scrollBar);
	}
	RETURNvoid_();
}

//void QAbstractScrollArea.setVerticalScrollBarPolicy(int arg0);
KMETHOD QAbstractScrollArea_setVerticalScrollBarPolicy(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QAbstractScrollArea *  qp = RawPtr_to(QAbstractScrollArea *, sfp[0]);
	if (qp) {
		Qt::ScrollBarPolicy arg0 = Int_to(Qt::ScrollBarPolicy, sfp[1]);
		qp->setVerticalScrollBarPolicy(arg0);
	}
	RETURNvoid_();
}

//void QAbstractScrollArea.setViewport(QWidget widget);
KMETHOD QAbstractScrollArea_setViewport(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QAbstractScrollArea *  qp = RawPtr_to(QAbstractScrollArea *, sfp[0]);
	if (qp) {
		QWidget*  widget = RawPtr_to(QWidget*, sfp[1]);
		qp->setViewport(widget);
	}
	RETURNvoid_();
}

//QScrollBar QAbstractScrollArea.getVerticalScrollBar();
KMETHOD QAbstractScrollArea_getVerticalScrollBar(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QAbstractScrollArea *  qp = RawPtr_to(QAbstractScrollArea *, sfp[0]);
	if (qp) {
		QScrollBar* ret_v = qp->verticalScrollBar();
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, (QScrollBar*)ret_v, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//int QAbstractScrollArea.getVerticalScrollBarPolicy();
KMETHOD QAbstractScrollArea_getVerticalScrollBarPolicy(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QAbstractScrollArea *  qp = RawPtr_to(QAbstractScrollArea *, sfp[0]);
	if (qp) {
		Qt::ScrollBarPolicy ret_v = qp->verticalScrollBarPolicy();
		RETURNi_(ret_v);
	} else {
		RETURNi_(0);
	}
}

//QWidget QAbstractScrollArea.getViewport();
KMETHOD QAbstractScrollArea_getViewport(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QAbstractScrollArea *  qp = RawPtr_to(QAbstractScrollArea *, sfp[0]);
	if (qp) {
		QWidget* ret_v = qp->viewport();
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, (QWidget*)ret_v, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}


DummyQAbstractScrollArea::DummyQAbstractScrollArea()
{
	CTX lctx = knh_getCurrentContext();
	(void)lctx;
	self = NULL;
	viewportEventPtr = new_empty_QRawPtr(lctx, QEvent);
	viewport_event_func = NULL;
	event_map = new map<string, knh_Func_t *>();
	slot_map = new map<string, knh_Func_t *>();
	event_map->insert(map<string, knh_Func_t *>::value_type("viewport-event", NULL));
}
DummyQAbstractScrollArea::~DummyQAbstractScrollArea()
{
	delete event_map;
	delete slot_map;
	event_map = NULL;
	slot_map = NULL;
}

void DummyQAbstractScrollArea::setSelf(knh_RawPtr_t *ptr)
{
	DummyQAbstractScrollArea::self = ptr;
	DummyQFrame::setSelf(ptr);
}

bool DummyQAbstractScrollArea::eventDispatcher(QEvent *event)
{
	bool ret = true;
	switch (event->type()) {
		ret = viewportEventDummy(dynamic_cast<QEvent*>(event));
		break;
	default:
		ret = DummyQFrame::eventDispatcher(event);
		break;
	}
	return ret;
}

bool DummyQAbstractScrollArea::viewportEventDummy(QEvent* event)
{
	if (viewport_event_func != NULL) {
		CTX lctx = knh_getCurrentContext();
		knh_sfp_t *lsfp = lctx->esp;
		KNH_SETv(lctx, lsfp[K_CALLDELTA+1].o, UPCAST(self));
		viewportEventPtr->rawptr = event;
		KNH_SETv(lctx, lsfp[K_CALLDELTA+2].o, (UPCAST(viewportEventPtr)));
		knh_Func_invoke(lctx, viewport_event_func, lsfp, 2);
		return true;
	}
	return false;
}

bool DummyQAbstractScrollArea::addEvent(knh_Func_t *callback_func, string str)
{
	std::map<string, knh_Func_t*>::iterator itr;// = DummyQAbstractScrollArea::event_map->bigin();
	if ((itr = DummyQAbstractScrollArea::event_map->find(str)) == DummyQAbstractScrollArea::event_map->end()) {
		bool ret = false;
		ret = DummyQFrame::addEvent(callback_func, str);
		return ret;
	} else {
		KNH_INITv((*event_map)[str], callback_func);
		viewport_event_func = (*event_map)["viewport-event"];
		return true;
	}
}

bool DummyQAbstractScrollArea::signalConnect(knh_Func_t *callback_func, string str)
{
	std::map<string, knh_Func_t*>::iterator itr;// = DummyQAbstractScrollArea::slot_map->bigin();
	if ((itr = DummyQAbstractScrollArea::slot_map->find(str)) == DummyQAbstractScrollArea::slot_map->end()) {
		bool ret = false;
		ret = DummyQFrame::signalConnect(callback_func, str);
		return ret;
	} else {
		KNH_INITv((*slot_map)[str], callback_func);
		return true;
	}
}

knh_Object_t** DummyQAbstractScrollArea::reftrace(CTX ctx, knh_RawPtr_t *p FTRARG)
{
//	(void)ctx; (void)p; (void)tail_;
//	fprintf(stderr, "DummyQAbstractScrollArea::reftrace p->rawptr=[%p]\n", p->rawptr);

	int list_size = 3;
	KNH_ENSUREREF(ctx, list_size);

	KNH_ADDNNREF(ctx, viewport_event_func);
	KNH_ADDNNREF(ctx, viewportEventPtr);

	KNH_SIZEREF(ctx);

	tail_ = DummyQFrame::reftrace(ctx, p, tail_);

	return tail_;
}

void DummyQAbstractScrollArea::connection(QObject *o)
{
	QAbstractScrollArea *p = dynamic_cast<QAbstractScrollArea*>(o);
	if (p != NULL) {
	}
	DummyQFrame::connection(o);
}

KQAbstractScrollArea::KQAbstractScrollArea(QWidget* parent) : QAbstractScrollArea(parent)
{
	magic_num = G_MAGIC_NUM;
	self = NULL;
	dummy = new DummyQAbstractScrollArea();
	dummy->connection((QObject*)this);
}

KQAbstractScrollArea::~KQAbstractScrollArea()
{
	delete dummy;
	dummy = NULL;
}
KMETHOD QAbstractScrollArea_addEvent(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	KQAbstractScrollArea *qp = RawPtr_to(KQAbstractScrollArea *, sfp[0]);
	const char *event_name = String_to(const char *, sfp[1]);
	knh_Func_t *callback_func = sfp[2].fo;
	if (qp != NULL) {
//		if (qp->event_map->find(event_name) == qp->event_map->end()) {
//			fprintf(stderr, "WARNING:[QAbstractScrollArea]unknown event name [%s]\n", event_name);
//			return;
//		}
		string str = string(event_name);
//		KNH_INITv((*(qp->event_map))[event_name], callback_func);
		if (!qp->dummy->addEvent(callback_func, str)) {
			fprintf(stderr, "WARNING:[QAbstractScrollArea]unknown event name [%s]\n", event_name);
			return;
		}
	}
	RETURNvoid_();
}
KMETHOD QAbstractScrollArea_signalConnect(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	KQAbstractScrollArea *qp = RawPtr_to(KQAbstractScrollArea *, sfp[0]);
	const char *signal_name = String_to(const char *, sfp[1]);
	knh_Func_t *callback_func = sfp[2].fo;
	if (qp != NULL) {
//		if (qp->slot_map->find(signal_name) == qp->slot_map->end()) {
//			fprintf(stderr, "WARNING:[QAbstractScrollArea]unknown signal name [%s]\n", signal_name);
//			return;
//		}
		string str = string(signal_name);
//		KNH_INITv((*(qp->slot_map))[signal_name], callback_func);
		if (!qp->dummy->signalConnect(callback_func, str)) {
			fprintf(stderr, "WARNING:[QAbstractScrollArea]unknown signal name [%s]\n", signal_name);
			return;
		}
	}
	RETURNvoid_();
}

static void QAbstractScrollArea_free(CTX ctx, knh_RawPtr_t *p)
{
	(void)ctx;
	if (!exec_flag) return;
	if (p->rawptr != NULL) {
		KQAbstractScrollArea *qp = (KQAbstractScrollArea *)p->rawptr;
		if (qp->magic_num == G_MAGIC_NUM) {
			delete qp;
			p->rawptr = NULL;
		} else {
			delete (QAbstractScrollArea*)qp;
			p->rawptr = NULL;
		}
	}
}
static void QAbstractScrollArea_reftrace(CTX ctx, knh_RawPtr_t *p FTRARG)
{
	if (p->rawptr != NULL) {
//		KQAbstractScrollArea *qp = (KQAbstractScrollArea *)p->rawptr;
		KQAbstractScrollArea *qp = static_cast<KQAbstractScrollArea*>(p->rawptr);
		qp->dummy->reftrace(ctx, p, tail_);
	}
}

static int QAbstractScrollArea_compareTo(knh_RawPtr_t *p1, knh_RawPtr_t *p2)
{
	return (p1->rawptr == p2->rawptr ? 0 : 1);
}

void KQAbstractScrollArea::setSelf(knh_RawPtr_t *ptr)
{
	self = ptr;
	dummy->setSelf(ptr);
}

bool KQAbstractScrollArea::event(QEvent *event)
{
	if (!dummy->eventDispatcher(event)) {
		QAbstractScrollArea::event(event);
		return false;
	}
//	QAbstractScrollArea::event(event);
	return true;
}



DEFAPI(void) defQAbstractScrollArea(CTX ctx, knh_class_t cid, knh_ClassDef_t *cdef)
{
	(void)ctx; (void) cid;
	cdef->name = "QAbstractScrollArea";
	cdef->free = QAbstractScrollArea_free;
	cdef->reftrace = QAbstractScrollArea_reftrace;
	cdef->compareTo = QAbstractScrollArea_compareTo;
}


