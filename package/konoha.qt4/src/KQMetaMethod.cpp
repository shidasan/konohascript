//int QMetaMethod.access();
KMETHOD QMetaMethod_access(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMetaMethod *  qp = RawPtr_to(QMetaMethod *, sfp[0]);
	if (qp) {
		QMetaMethod::Access ret_v = qp->access();
		RETURNi_(ret_v);
	} else {
		RETURNi_(0);
	}
}

//boolean QMetaMethod.invoke(QObject object, int connectionType, QGenericReturnArgument returnValue, QGenericArgument val0);
KMETHOD QMetaMethod_invoke(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMetaMethod *  qp = RawPtr_to(QMetaMethod *, sfp[0]);
	if (qp) {
		QObject*  object = RawPtr_to(QObject*, sfp[1]);
		Qt::ConnectionType connectionType = Int_to(Qt::ConnectionType, sfp[2]);
		QGenericReturnArgument  returnValue = *RawPtr_to(QGenericReturnArgument *, sfp[3]);
		QGenericArgument  val0 = *RawPtr_to(QGenericArgument *, sfp[4]);
		bool ret_v = qp->invoke(object, connectionType, returnValue, val0);
		RETURNb_(ret_v);
	} else {
		RETURNb_(false);
	}
}

/*
//boolean QMetaMethod.invoke(QObject object, QGenericReturnArgument returnValue, QGenericArgument val0);
KMETHOD QMetaMethod_invoke(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMetaMethod *  qp = RawPtr_to(QMetaMethod *, sfp[0]);
	if (qp) {
		QObject*  object = RawPtr_to(QObject*, sfp[1]);
		QGenericReturnArgument  returnValue = *RawPtr_to(QGenericReturnArgument *, sfp[2]);
		QGenericArgument  val0 = *RawPtr_to(QGenericArgument *, sfp[3]);
		bool ret_v = qp->invoke(object, returnValue, val0);
		RETURNb_(ret_v);
	} else {
		RETURNb_(false);
	}
}
*/
/*
//boolean QMetaMethod.invoke(QObject object, int connectionType, QGenericArgument val0);
KMETHOD QMetaMethod_invoke(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMetaMethod *  qp = RawPtr_to(QMetaMethod *, sfp[0]);
	if (qp) {
		QObject*  object = RawPtr_to(QObject*, sfp[1]);
		Qt::ConnectionType connectionType = Int_to(Qt::ConnectionType, sfp[2]);
		QGenericArgument  val0 = *RawPtr_to(QGenericArgument *, sfp[3]);
		bool ret_v = qp->invoke(object, connectionType, val0);
		RETURNb_(ret_v);
	} else {
		RETURNb_(false);
	}
}
*/
/*
//boolean QMetaMethod.invoke(QObject object, QGenericArgument val0);
KMETHOD QMetaMethod_invoke(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMetaMethod *  qp = RawPtr_to(QMetaMethod *, sfp[0]);
	if (qp) {
		QObject*  object = RawPtr_to(QObject*, sfp[1]);
		QGenericArgument  val0 = *RawPtr_to(QGenericArgument *, sfp[2]);
		bool ret_v = qp->invoke(object, val0);
		RETURNb_(ret_v);
	} else {
		RETURNb_(false);
	}
}
*/
//int QMetaMethod.methodIndex();
KMETHOD QMetaMethod_methodIndex(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMetaMethod *  qp = RawPtr_to(QMetaMethod *, sfp[0]);
	if (qp) {
		int ret_v = qp->methodIndex();
		RETURNi_(ret_v);
	} else {
		RETURNi_(0);
	}
}

//int QMetaMethod.methodType();
KMETHOD QMetaMethod_methodType(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMetaMethod *  qp = RawPtr_to(QMetaMethod *, sfp[0]);
	if (qp) {
		QMetaMethod::MethodType ret_v = qp->methodType();
		RETURNi_(ret_v);
	} else {
		RETURNi_(0);
	}
}

//Array<QByteArray> QMetaMethod.parameterNames();
KMETHOD QMetaMethod_parameterNames(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMetaMethod *  qp = RawPtr_to(QMetaMethod *, sfp[0]);
	if (qp) {
		QList<QByteArray> ret_v = qp->parameterNames();
		int list_size = ret_v.size();
		knh_Array_t *a = new_Array0(ctx, list_size);
		knh_class_t cid = knh_getcid(ctx, STEXT("QByteArray"));
		for (int n = 0; n < list_size; n++) {
			QByteArray *ret_v_ = new QByteArray(ret_v[n]);
			knh_RawPtr_t *p = new_RawPtr(ctx, ClassTBL(cid), ret_v_);
			knh_Array_add(ctx, a, (knh_Object_t *)p);
		}
		RETURN_(a);
	} else {
		RETURN_(KNH_NULL);
	}
}
	

//Array<QByteArray> QMetaMethod.parameterTypes();
KMETHOD QMetaMethod_parameterTypes(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMetaMethod *  qp = RawPtr_to(QMetaMethod *, sfp[0]);
	if (qp) {
		QList<QByteArray> ret_v = qp->parameterTypes();
		int list_size = ret_v.size();
		knh_Array_t *a = new_Array0(ctx, list_size);
		knh_class_t cid = knh_getcid(ctx, STEXT("QByteArray"));
		for (int n = 0; n < list_size; n++) {
			QByteArray *ret_v_ = new QByteArray(ret_v[n]);
			knh_RawPtr_t *p = new_RawPtr(ctx, ClassTBL(cid), ret_v_);
			knh_Array_add(ctx, a, (knh_Object_t *)p);
		}
		RETURN_(a);
	} else {
		RETURN_(KNH_NULL);
	}
}
	

//String QMetaMethod.signature();
KMETHOD QMetaMethod_signature(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMetaMethod *  qp = RawPtr_to(QMetaMethod *, sfp[0]);
	if (qp) {
		const char* ret_v = qp->signature();
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, (char*)ret_v, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//String QMetaMethod.tag();
KMETHOD QMetaMethod_tag(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMetaMethod *  qp = RawPtr_to(QMetaMethod *, sfp[0]);
	if (qp) {
		const char* ret_v = qp->tag();
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, (char*)ret_v, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//String QMetaMethod.typeName();
KMETHOD QMetaMethod_typeName(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMetaMethod *  qp = RawPtr_to(QMetaMethod *, sfp[0]);
	if (qp) {
		const char* ret_v = qp->typeName();
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, (char*)ret_v, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//Array<String> QMetaMethod.parents();
KMETHOD QMetaMethod_parents(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QMetaMethod *qp = RawPtr_to(QMetaMethod*, sfp[0]);
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

DummyQMetaMethod::DummyQMetaMethod()
{
	CTX lctx = knh_getCurrentContext();
	(void)lctx;
	self = NULL;
	event_map = new map<string, knh_Func_t *>();
	slot_map = new map<string, knh_Func_t *>();
}
DummyQMetaMethod::~DummyQMetaMethod()
{
	delete event_map;
	delete slot_map;
	event_map = NULL;
	slot_map = NULL;
}

void DummyQMetaMethod::setSelf(knh_RawPtr_t *ptr)
{
	DummyQMetaMethod::self = ptr;
}

bool DummyQMetaMethod::eventDispatcher(QEvent *event)
{
	bool ret = true;
	switch (event->type()) {
	default:
		ret = false;
		break;
	}
	return ret;
}

bool DummyQMetaMethod::addEvent(knh_Func_t *callback_func, string str)
{
	std::map<string, knh_Func_t*>::iterator itr;// = DummyQMetaMethod::event_map->bigin();
	if ((itr = DummyQMetaMethod::event_map->find(str)) == DummyQMetaMethod::event_map->end()) {
		bool ret = false;
		return ret;
	} else {
		KNH_INITv((*event_map)[str], callback_func);
		return true;
	}
}

bool DummyQMetaMethod::signalConnect(knh_Func_t *callback_func, string str)
{
	std::map<string, knh_Func_t*>::iterator itr;// = DummyQMetaMethod::slot_map->bigin();
	if ((itr = DummyQMetaMethod::slot_map->find(str)) == DummyQMetaMethod::slot_map->end()) {
		bool ret = false;
		return ret;
	} else {
		KNH_INITv((*slot_map)[str], callback_func);
		return true;
	}
}

knh_Object_t** DummyQMetaMethod::reftrace(CTX ctx, knh_RawPtr_t *p FTRARG)
{
	(void)ctx; (void)p; (void)tail_;
//	fprintf(stderr, "DummyQMetaMethod::reftrace p->rawptr=[%p]\n", p->rawptr);


	return tail_;
}

void DummyQMetaMethod::connection(QObject *o)
{
	QMetaMethod *p = dynamic_cast<QMetaMethod*>(o);
	if (p != NULL) {
	}
}

KQMetaMethod::~KQMetaMethod()
{
	delete dummy;
	dummy = NULL;
}
KMETHOD QMetaMethod_addEvent(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	KQMetaMethod *qp = RawPtr_to(KQMetaMethod *, sfp[0]);
	const char *event_name = String_to(const char *, sfp[1]);
	knh_Func_t *callback_func = sfp[2].fo;
	if (qp != NULL) {
//		if (qp->event_map->find(event_name) == qp->event_map->end()) {
//			fprintf(stderr, "WARNING:[QMetaMethod]unknown event name [%s]\n", event_name);
//			return;
//		}
		string str = string(event_name);
//		KNH_INITv((*(qp->event_map))[event_name], callback_func);
		if (!qp->dummy->addEvent(callback_func, str)) {
			fprintf(stderr, "WARNING:[QMetaMethod]unknown event name [%s]\n", event_name);
			return;
		}
	}
	RETURNvoid_();
}
KMETHOD QMetaMethod_signalConnect(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	KQMetaMethod *qp = RawPtr_to(KQMetaMethod *, sfp[0]);
	const char *signal_name = String_to(const char *, sfp[1]);
	knh_Func_t *callback_func = sfp[2].fo;
	if (qp != NULL) {
//		if (qp->slot_map->find(signal_name) == qp->slot_map->end()) {
//			fprintf(stderr, "WARNING:[QMetaMethod]unknown signal name [%s]\n", signal_name);
//			return;
//		}
		string str = string(signal_name);
//		KNH_INITv((*(qp->slot_map))[signal_name], callback_func);
		if (!qp->dummy->signalConnect(callback_func, str)) {
			fprintf(stderr, "WARNING:[QMetaMethod]unknown signal name [%s]\n", signal_name);
			return;
		}
	}
	RETURNvoid_();
}

static void QMetaMethod_free(CTX ctx, knh_RawPtr_t *p)
{
	(void)ctx;
	if (!exec_flag) return;
	if (p->rawptr != NULL) {
		KQMetaMethod *qp = (KQMetaMethod *)p->rawptr;
		if (qp->magic_num == G_MAGIC_NUM) {
			delete qp;
			p->rawptr = NULL;
		} else {
			delete (QMetaMethod*)qp;
			p->rawptr = NULL;
		}
	}
}
static void QMetaMethod_reftrace(CTX ctx, knh_RawPtr_t *p FTRARG)
{
	if (p->rawptr != NULL) {
//		KQMetaMethod *qp = (KQMetaMethod *)p->rawptr;
		KQMetaMethod *qp = static_cast<KQMetaMethod*>(p->rawptr);
		qp->dummy->reftrace(ctx, p, tail_);
	}
}

static int QMetaMethod_compareTo(knh_RawPtr_t *p1, knh_RawPtr_t *p2)
{
	return (p1->rawptr == p2->rawptr ? 0 : 1);
}

void KQMetaMethod::setSelf(knh_RawPtr_t *ptr)
{
	self = ptr;
	dummy->setSelf(ptr);
}

static knh_IntData_t QMetaMethodConstInt[] = {
	{"Private", QMetaMethod::Private},
	{"Protected", QMetaMethod::Protected},
	{"Public", QMetaMethod::Public},
	{"Method", QMetaMethod::Method},
	{"Signal", QMetaMethod::Signal},
	{"Slot", QMetaMethod::Slot},
	{"Constructor", QMetaMethod::Constructor},
	{NULL, 0}
};

DEFAPI(void) constQMetaMethod(CTX ctx, knh_class_t cid, const knh_LoaderAPI_t *kapi) {
	kapi->loadClassIntConst(ctx, cid, QMetaMethodConstInt);
}


DEFAPI(void) defQMetaMethod(CTX ctx, knh_class_t cid, knh_ClassDef_t *cdef)
{
	(void)ctx; (void) cid;
	cdef->name = "QMetaMethod";
	cdef->free = QMetaMethod_free;
	cdef->reftrace = QMetaMethod_reftrace;
	cdef->compareTo = QMetaMethod_compareTo;
}


