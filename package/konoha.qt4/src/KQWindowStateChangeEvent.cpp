//QtWindowStates QWindowStateChangeEvent.oldState();
KMETHOD QWindowStateChangeEvent_oldState(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QWindowStateChangeEvent *  qp = RawPtr_to(QWindowStateChangeEvent *, sfp[0]);
	if (qp) {
		Qt::WindowStates ret_v = qp->oldState();
		Qt::WindowStates *ret_v_ = new Qt::WindowStates(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}


DummyQWindowStateChangeEvent::DummyQWindowStateChangeEvent()
{
	CTX lctx = knh_getCurrentContext();
	(void)lctx;
	self = NULL;
	event_map = new map<string, knh_Func_t *>();
	slot_map = new map<string, knh_Func_t *>();
}
DummyQWindowStateChangeEvent::~DummyQWindowStateChangeEvent()
{
	delete event_map;
	delete slot_map;
	event_map = NULL;
	slot_map = NULL;
}

void DummyQWindowStateChangeEvent::setSelf(knh_RawPtr_t *ptr)
{
	DummyQWindowStateChangeEvent::self = ptr;
	DummyQEvent::setSelf(ptr);
}

bool DummyQWindowStateChangeEvent::eventDispatcher(QEvent *event)
{
	bool ret = true;
	switch (event->type()) {
	default:
		ret = DummyQEvent::eventDispatcher(event);
		break;
	}
	return ret;
}

bool DummyQWindowStateChangeEvent::addEvent(knh_Func_t *callback_func, string str)
{
	std::map<string, knh_Func_t*>::iterator itr;// = DummyQWindowStateChangeEvent::event_map->bigin();
	if ((itr = DummyQWindowStateChangeEvent::event_map->find(str)) == DummyQWindowStateChangeEvent::event_map->end()) {
		bool ret = false;
		ret = DummyQEvent::addEvent(callback_func, str);
		return ret;
	} else {
		KNH_INITv((*event_map)[str], callback_func);
		return true;
	}
}

bool DummyQWindowStateChangeEvent::signalConnect(knh_Func_t *callback_func, string str)
{
	std::map<string, knh_Func_t*>::iterator itr;// = DummyQWindowStateChangeEvent::slot_map->bigin();
	if ((itr = DummyQWindowStateChangeEvent::slot_map->find(str)) == DummyQWindowStateChangeEvent::slot_map->end()) {
		bool ret = false;
		ret = DummyQEvent::signalConnect(callback_func, str);
		return ret;
	} else {
		KNH_INITv((*slot_map)[str], callback_func);
		return true;
	}
}

knh_Object_t** DummyQWindowStateChangeEvent::reftrace(CTX ctx, knh_RawPtr_t *p FTRARG)
{
	(void)ctx; (void)p; (void)tail_;
//	fprintf(stderr, "DummyQWindowStateChangeEvent::reftrace p->rawptr=[%p]\n", p->rawptr);

	tail_ = DummyQEvent::reftrace(ctx, p, tail_);

	return tail_;
}

void DummyQWindowStateChangeEvent::connection(QObject *o)
{
	QWindowStateChangeEvent *p = dynamic_cast<QWindowStateChangeEvent*>(o);
	if (p != NULL) {
	}
	DummyQEvent::connection(o);
}

KQWindowStateChangeEvent::~KQWindowStateChangeEvent()
{
	delete dummy;
	dummy = NULL;
}
KMETHOD QWindowStateChangeEvent_addEvent(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	KQWindowStateChangeEvent *qp = RawPtr_to(KQWindowStateChangeEvent *, sfp[0]);
	const char *event_name = String_to(const char *, sfp[1]);
	knh_Func_t *callback_func = sfp[2].fo;
	if (qp != NULL) {
//		if (qp->event_map->find(event_name) == qp->event_map->end()) {
//			fprintf(stderr, "WARNING:[QWindowStateChangeEvent]unknown event name [%s]\n", event_name);
//			return;
//		}
		string str = string(event_name);
//		KNH_INITv((*(qp->event_map))[event_name], callback_func);
		if (!qp->dummy->addEvent(callback_func, str)) {
			fprintf(stderr, "WARNING:[QWindowStateChangeEvent]unknown event name [%s]\n", event_name);
			return;
		}
	}
	RETURNvoid_();
}
KMETHOD QWindowStateChangeEvent_signalConnect(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	KQWindowStateChangeEvent *qp = RawPtr_to(KQWindowStateChangeEvent *, sfp[0]);
	const char *signal_name = String_to(const char *, sfp[1]);
	knh_Func_t *callback_func = sfp[2].fo;
	if (qp != NULL) {
//		if (qp->slot_map->find(signal_name) == qp->slot_map->end()) {
//			fprintf(stderr, "WARNING:[QWindowStateChangeEvent]unknown signal name [%s]\n", signal_name);
//			return;
//		}
		string str = string(signal_name);
//		KNH_INITv((*(qp->slot_map))[signal_name], callback_func);
		if (!qp->dummy->signalConnect(callback_func, str)) {
			fprintf(stderr, "WARNING:[QWindowStateChangeEvent]unknown signal name [%s]\n", signal_name);
			return;
		}
	}
	RETURNvoid_();
}

static void QWindowStateChangeEvent_free(CTX ctx, knh_RawPtr_t *p)
{
	(void)ctx;
	if (!exec_flag) return;
	if (p->rawptr != NULL) {
		KQWindowStateChangeEvent *qp = (KQWindowStateChangeEvent *)p->rawptr;
		if (qp->magic_num == G_MAGIC_NUM) {
			delete qp;
			p->rawptr = NULL;
		} else {
			delete (QWindowStateChangeEvent*)qp;
			p->rawptr = NULL;
		}
	}
}
static void QWindowStateChangeEvent_reftrace(CTX ctx, knh_RawPtr_t *p FTRARG)
{
	if (p->rawptr != NULL) {
//		KQWindowStateChangeEvent *qp = (KQWindowStateChangeEvent *)p->rawptr;
		KQWindowStateChangeEvent *qp = static_cast<KQWindowStateChangeEvent*>(p->rawptr);
		qp->dummy->reftrace(ctx, p, tail_);
	}
}

static int QWindowStateChangeEvent_compareTo(knh_RawPtr_t *p1, knh_RawPtr_t *p2)
{
	return (p1->rawptr == p2->rawptr ? 0 : 1);
}

void KQWindowStateChangeEvent::setSelf(knh_RawPtr_t *ptr)
{
	self = ptr;
	dummy->setSelf(ptr);
}



DEFAPI(void) defQWindowStateChangeEvent(CTX ctx, knh_class_t cid, knh_ClassDef_t *cdef)
{
	(void)ctx; (void) cid;
	cdef->name = "QWindowStateChangeEvent";
	cdef->free = QWindowStateChangeEvent_free;
	cdef->reftrace = QWindowStateChangeEvent_reftrace;
	cdef->compareTo = QWindowStateChangeEvent_compareTo;
}


