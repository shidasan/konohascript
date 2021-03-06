//int QElapsedTimer.elapsed();
KMETHOD QElapsedTimer_elapsed(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QElapsedTimer *  qp = RawPtr_to(QElapsedTimer *, sfp[0]);
	if (qp) {
		qint64 ret_v = qp->elapsed();
		qint64 *ret_v_ = new qint64(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//boolean QElapsedTimer.hasExpired(int timeout);
KMETHOD QElapsedTimer_hasExpired(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QElapsedTimer *  qp = RawPtr_to(QElapsedTimer *, sfp[0]);
	if (qp) {
		qint64 timeout = Int_to(qint64, sfp[1]);
		bool ret_v = qp->hasExpired(timeout);
		RETURNb_(ret_v);
	} else {
		RETURNb_(false);
	}
}

//void QElapsedTimer.invalidate();
KMETHOD QElapsedTimer_invalidate(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QElapsedTimer *  qp = RawPtr_to(QElapsedTimer *, sfp[0]);
	if (qp) {
		qp->invalidate();
	}
	RETURNvoid_();
}

//int QElapsedTimer.msecsSinceReference();
KMETHOD QElapsedTimer_msecsSinceReference(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QElapsedTimer *  qp = RawPtr_to(QElapsedTimer *, sfp[0]);
	if (qp) {
		qint64 ret_v = qp->msecsSinceReference();
		qint64 *ret_v_ = new qint64(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//int QElapsedTimer.msecsTo(QElapsedTimer other);
KMETHOD QElapsedTimer_msecsTo(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QElapsedTimer *  qp = RawPtr_to(QElapsedTimer *, sfp[0]);
	if (qp) {
		const QElapsedTimer  other = *RawPtr_to(const QElapsedTimer *, sfp[1]);
		qint64 ret_v = qp->msecsTo(other);
		qint64 *ret_v_ = new qint64(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//int QElapsedTimer.restart();
KMETHOD QElapsedTimer_restart(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QElapsedTimer *  qp = RawPtr_to(QElapsedTimer *, sfp[0]);
	if (qp) {
		qint64 ret_v = qp->restart();
		qint64 *ret_v_ = new qint64(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//int QElapsedTimer.secsTo(QElapsedTimer other);
KMETHOD QElapsedTimer_secsTo(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QElapsedTimer *  qp = RawPtr_to(QElapsedTimer *, sfp[0]);
	if (qp) {
		const QElapsedTimer  other = *RawPtr_to(const QElapsedTimer *, sfp[1]);
		qint64 ret_v = qp->secsTo(other);
		qint64 *ret_v_ = new qint64(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//void QElapsedTimer.start();
KMETHOD QElapsedTimer_start(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QElapsedTimer *  qp = RawPtr_to(QElapsedTimer *, sfp[0]);
	if (qp) {
		qp->start();
	}
	RETURNvoid_();
}

//int QElapsedTimer.clockType();
KMETHOD QElapsedTimer_clockType(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	if (true) {
		QElapsedTimer::ClockType ret_v = QElapsedTimer::clockType();
		RETURNi_(ret_v);
	} else {
		RETURNi_(0);
	}
}

//boolean QElapsedTimer.isMonotonic();
KMETHOD QElapsedTimer_isMonotonic(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	if (true) {
		bool ret_v = QElapsedTimer::isMonotonic();
		RETURNb_(ret_v);
	} else {
		RETURNb_(false);
	}
}

//Array<String> QElapsedTimer.parents();
KMETHOD QElapsedTimer_parents(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QElapsedTimer *qp = RawPtr_to(QElapsedTimer*, sfp[0]);
	if (qp != NULL) {
		int size = 10;
		knh_Array_t *a = new_Array0(ctx, size);
		const knh_ClassTBL_t *ct = sfp[0].p->h.cTBL;
		while(ct->supcid != CLASS_Object) {
			ct = ct->supTBL;
			knh_Array_add(ctx, a, (knh_Object_t *)ct->lname);
		}
		RETURN_(a);
	} else {
		RETURN_(KNH_NULL);
	}
}

DummyQElapsedTimer::DummyQElapsedTimer()
{
	CTX lctx = knh_getCurrentContext();
	(void)lctx;
	self = NULL;
	event_map = new map<string, knh_Func_t *>();
	slot_map = new map<string, knh_Func_t *>();
}
DummyQElapsedTimer::~DummyQElapsedTimer()
{
	delete event_map;
	delete slot_map;
	event_map = NULL;
	slot_map = NULL;
}

void DummyQElapsedTimer::setSelf(knh_RawPtr_t *ptr)
{
	DummyQElapsedTimer::self = ptr;
}

bool DummyQElapsedTimer::eventDispatcher(QEvent *event)
{
	bool ret = true;
	switch (event->type()) {
	default:
		ret = false;
		break;
	}
	return ret;
}

bool DummyQElapsedTimer::addEvent(knh_Func_t *callback_func, string str)
{
	std::map<string, knh_Func_t*>::iterator itr;// = DummyQElapsedTimer::event_map->bigin();
	if ((itr = DummyQElapsedTimer::event_map->find(str)) == DummyQElapsedTimer::event_map->end()) {
		bool ret = false;
		return ret;
	} else {
		KNH_INITv((*event_map)[str], callback_func);
		return true;
	}
}

bool DummyQElapsedTimer::signalConnect(knh_Func_t *callback_func, string str)
{
	std::map<string, knh_Func_t*>::iterator itr;// = DummyQElapsedTimer::slot_map->bigin();
	if ((itr = DummyQElapsedTimer::slot_map->find(str)) == DummyQElapsedTimer::slot_map->end()) {
		bool ret = false;
		return ret;
	} else {
		KNH_INITv((*slot_map)[str], callback_func);
		return true;
	}
}

knh_Object_t** DummyQElapsedTimer::reftrace(CTX ctx, knh_RawPtr_t *p FTRARG)
{
	(void)ctx; (void)p; (void)tail_;
//	fprintf(stderr, "DummyQElapsedTimer::reftrace p->rawptr=[%p]\n", p->rawptr);


	return tail_;
}

void DummyQElapsedTimer::connection(QObject *o)
{
	QElapsedTimer *p = dynamic_cast<QElapsedTimer*>(o);
	if (p != NULL) {
	}
}

KQElapsedTimer::~KQElapsedTimer()
{
	delete dummy;
	dummy = NULL;
}
KMETHOD QElapsedTimer_addEvent(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	KQElapsedTimer *qp = RawPtr_to(KQElapsedTimer *, sfp[0]);
	const char *event_name = String_to(const char *, sfp[1]);
	knh_Func_t *callback_func = sfp[2].fo;
	if (qp != NULL) {
//		if (qp->event_map->find(event_name) == qp->event_map->end()) {
//			fprintf(stderr, "WARNING:[QElapsedTimer]unknown event name [%s]\n", event_name);
//			return;
//		}
		string str = string(event_name);
//		KNH_INITv((*(qp->event_map))[event_name], callback_func);
		if (!qp->dummy->addEvent(callback_func, str)) {
			fprintf(stderr, "WARNING:[QElapsedTimer]unknown event name [%s]\n", event_name);
			return;
		}
	}
	RETURNvoid_();
}
KMETHOD QElapsedTimer_signalConnect(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	KQElapsedTimer *qp = RawPtr_to(KQElapsedTimer *, sfp[0]);
	const char *signal_name = String_to(const char *, sfp[1]);
	knh_Func_t *callback_func = sfp[2].fo;
	if (qp != NULL) {
//		if (qp->slot_map->find(signal_name) == qp->slot_map->end()) {
//			fprintf(stderr, "WARNING:[QElapsedTimer]unknown signal name [%s]\n", signal_name);
//			return;
//		}
		string str = string(signal_name);
//		KNH_INITv((*(qp->slot_map))[signal_name], callback_func);
		if (!qp->dummy->signalConnect(callback_func, str)) {
			fprintf(stderr, "WARNING:[QElapsedTimer]unknown signal name [%s]\n", signal_name);
			return;
		}
	}
	RETURNvoid_();
}

static void QElapsedTimer_free(CTX ctx, knh_RawPtr_t *p)
{
	(void)ctx;
	if (!exec_flag) return;
	if (p->rawptr != NULL) {
		KQElapsedTimer *qp = (KQElapsedTimer *)p->rawptr;
		if (qp->magic_num == G_MAGIC_NUM) {
			delete qp;
			p->rawptr = NULL;
		} else {
			delete (QElapsedTimer*)qp;
			p->rawptr = NULL;
		}
	}
}
static void QElapsedTimer_reftrace(CTX ctx, knh_RawPtr_t *p FTRARG)
{
	if (p->rawptr != NULL) {
//		KQElapsedTimer *qp = (KQElapsedTimer *)p->rawptr;
		KQElapsedTimer *qp = static_cast<KQElapsedTimer*>(p->rawptr);
		qp->dummy->reftrace(ctx, p, tail_);
	}
}

static int QElapsedTimer_compareTo(knh_RawPtr_t *p1, knh_RawPtr_t *p2)
{
	return (*static_cast<QElapsedTimer*>(p1->rawptr) == *static_cast<QElapsedTimer*>(p2->rawptr) ? 0 : 1);
}

void KQElapsedTimer::setSelf(knh_RawPtr_t *ptr)
{
	self = ptr;
	dummy->setSelf(ptr);
}

static knh_IntData_t QElapsedTimerConstInt[] = {
	{"SystemTime", QElapsedTimer::SystemTime},
	{"MonotonicClock", QElapsedTimer::MonotonicClock},
	{"TickCounter", QElapsedTimer::TickCounter},
	{"MachAbsoluteTime", QElapsedTimer::MachAbsoluteTime},
	{NULL, 0}
};

DEFAPI(void) constQElapsedTimer(CTX ctx, knh_class_t cid, const knh_LoaderAPI_t *kapi) {
	kapi->loadClassIntConst(ctx, cid, QElapsedTimerConstInt);
}


DEFAPI(void) defQElapsedTimer(CTX ctx, knh_class_t cid, knh_ClassDef_t *cdef)
{
	(void)ctx; (void) cid;
	cdef->name = "QElapsedTimer";
	cdef->free = QElapsedTimer_free;
	cdef->reftrace = QElapsedTimer_reftrace;
	cdef->compareTo = QElapsedTimer_compareTo;
}


