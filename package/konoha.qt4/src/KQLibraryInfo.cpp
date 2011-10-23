//QDate QLibraryInfo.buildDate();
KMETHOD QLibraryInfo_buildDate(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QLibraryInfo *  qp = RawPtr_to(QLibraryInfo *, sfp[0]);
	if (qp != NULL) {
		QDate ret_v = qp->buildDate();
		QDate *ret_v_ = new QDate(ret_v);
		knh_RawPtr_t *rptr = new_ReturnCppObject(ctx, sfp, ret_v_, NULL);
		RETURN_(rptr);
	} else {
		RETURN_(KNH_NULL);
	}
}

//String QLibraryInfo.buildKey();
KMETHOD QLibraryInfo_buildKey(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QLibraryInfo *  qp = RawPtr_to(QLibraryInfo *, sfp[0]);
	if (qp != NULL) {
		QString ret_v = qp->buildKey();
		const char *ret_c = ret_v.toLocal8Bit().data();
		RETURN_(new_String(ctx, ret_c));
	} else {
		RETURN_(KNH_NULL);
	}
}

//String QLibraryInfo.licensedProducts();
KMETHOD QLibraryInfo_licensedProducts(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QLibraryInfo *  qp = RawPtr_to(QLibraryInfo *, sfp[0]);
	if (qp != NULL) {
		QString ret_v = qp->licensedProducts();
		const char *ret_c = ret_v.toLocal8Bit().data();
		RETURN_(new_String(ctx, ret_c));
	} else {
		RETURN_(KNH_NULL);
	}
}

//String QLibraryInfo.licensee();
KMETHOD QLibraryInfo_licensee(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QLibraryInfo *  qp = RawPtr_to(QLibraryInfo *, sfp[0]);
	if (qp != NULL) {
		QString ret_v = qp->licensee();
		const char *ret_c = ret_v.toLocal8Bit().data();
		RETURN_(new_String(ctx, ret_c));
	} else {
		RETURN_(KNH_NULL);
	}
}

//String QLibraryInfo.location(int loc);
KMETHOD QLibraryInfo_location(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	QLibraryInfo *  qp = RawPtr_to(QLibraryInfo *, sfp[0]);
	if (qp != NULL) {
		QLibraryInfo::LibraryLocation loc = Int_to(QLibraryInfo::LibraryLocation, sfp[1]);
		QString ret_v = qp->location(loc);
		const char *ret_c = ret_v.toLocal8Bit().data();
		RETURN_(new_String(ctx, ret_c));
	} else {
		RETURN_(KNH_NULL);
	}
}


DummyQLibraryInfo::DummyQLibraryInfo()
{
	self = NULL;
	event_map = new map<string, knh_Func_t *>();
	slot_map = new map<string, knh_Func_t *>();
}

void DummyQLibraryInfo::setSelf(knh_RawPtr_t *ptr)
{
	DummyQLibraryInfo::self = ptr;
}

bool DummyQLibraryInfo::eventDispatcher(QEvent *event)
{
	bool ret = true;
	switch (event->type()) {
	default:
		ret = false;
		break;
	}
	return ret;
}

bool DummyQLibraryInfo::addEvent(knh_Func_t *callback_func, string str)
{
	std::map<string, knh_Func_t*>::iterator itr;// = DummyQLibraryInfo::event_map->bigin();
	if ((itr = DummyQLibraryInfo::event_map->find(str)) == DummyQLibraryInfo::event_map->end()) {
		bool ret = false;
		return ret;
	} else {
		KNH_INITv((*event_map)[str], callback_func);
		return true;
	}
}

bool DummyQLibraryInfo::signalConnect(knh_Func_t *callback_func, string str)
{
	std::map<string, knh_Func_t*>::iterator itr;// = DummyQLibraryInfo::slot_map->bigin();
	if ((itr = DummyQLibraryInfo::slot_map->find(str)) == DummyQLibraryInfo::slot_map->end()) {
		bool ret = false;
		return ret;
	} else {
		KNH_INITv((*slot_map)[str], callback_func);
		return true;
	}
}


void DummyQLibraryInfo::connection(QObject *o)
{
	return;
}

KMETHOD QLibraryInfo_addEvent(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	KQLibraryInfo *qp = RawPtr_to(KQLibraryInfo *, sfp[0]);
	const char *event_name = String_to(const char *, sfp[1]);
	knh_Func_t *callback_func = sfp[2].fo;
	if (qp != NULL) {
//		if (qp->event_map->find(event_name) == qp->event_map->end()) {
//			fprintf(stderr, "WARNING:[QLibraryInfo]unknown event name [%s]\n", event_name);
//			return;
//		}
		string str = string(event_name);
//		KNH_INITv((*(qp->event_map))[event_name], callback_func);
		if (!qp->dummy->addEvent(callback_func, str)) {
			fprintf(stderr, "WARNING:[QLibraryInfo]unknown event name [%s]\n", event_name);
			return;
		}
	}
	RETURNvoid_();
}
KMETHOD QLibraryInfo_signalConnect(CTX ctx, knh_sfp_t *sfp _RIX)
{
	(void)ctx;
	KQLibraryInfo *qp = RawPtr_to(KQLibraryInfo *, sfp[0]);
	const char *signal_name = String_to(const char *, sfp[1]);
	knh_Func_t *callback_func = sfp[2].fo;
	if (qp != NULL) {
//		if (qp->slot_map->find(signal_name) == qp->slot_map->end()) {
//			fprintf(stderr, "WARNING:[QLibraryInfo]unknown signal name [%s]\n", signal_name);
//			return;
//		}
		string str = string(signal_name);
//		KNH_INITv((*(qp->slot_map))[signal_name], callback_func);
		if (!qp->dummy->signalConnect(callback_func, str)) {
			fprintf(stderr, "WARNING:[QLibraryInfo]unknown signal name [%s]\n", signal_name);
			return;
		}
	}
	RETURNvoid_();
}

static void QLibraryInfo_free(CTX ctx, knh_RawPtr_t *p)
{
	(void)ctx;
	if (p->rawptr != NULL) {
		KQLibraryInfo *qp = (KQLibraryInfo *)p->rawptr;
		(void)qp;
		//delete qp;
	}
}
static void QLibraryInfo_reftrace(CTX ctx, knh_RawPtr_t *p FTRARG)
{
	(void)ctx; (void)p; (void)tail_;
	int list_size = 0;
	KNH_ENSUREREF(ctx, list_size);

	if (p->rawptr != NULL) {
		KQLibraryInfo *qp = (KQLibraryInfo *)p->rawptr;
		(void)qp;
	}
}

static int QLibraryInfo_compareTo(knh_RawPtr_t *p1, knh_RawPtr_t *p2)
{
	return (p1->rawptr == p2->rawptr ? 0 : 1);
}

void KQLibraryInfo::setSelf(knh_RawPtr_t *ptr)
{
	self = ptr;
	dummy->setSelf(ptr);
}

DEFAPI(void) defQLibraryInfo(CTX ctx, knh_class_t cid, knh_ClassDef_t *cdef)
{
	(void)ctx; (void) cid;
	cdef->name = "QLibraryInfo";
	cdef->free = QLibraryInfo_free;
	cdef->reftrace = QLibraryInfo_reftrace;
	cdef->compareTo = QLibraryInfo_compareTo;
}

static knh_IntData_t QLibraryInfoConstInt[] = {
	{"PrefixPath", QLibraryInfo::PrefixPath},
	{"DocumentationPath", QLibraryInfo::DocumentationPath},
	{"HeadersPath", QLibraryInfo::HeadersPath},
	{"LibrariesPath", QLibraryInfo::LibrariesPath},
	{"BinariesPath", QLibraryInfo::BinariesPath},
	{"PluginsPath", QLibraryInfo::PluginsPath},
	{"ImportsPath", QLibraryInfo::ImportsPath},
	{"DataPath", QLibraryInfo::DataPath},
	{"TranslationsPath", QLibraryInfo::TranslationsPath},
	{"SettingsPath", QLibraryInfo::SettingsPath},
	{"ExamplesPath", QLibraryInfo::ExamplesPath},
	{"DemosPath", QLibraryInfo::DemosPath},
	{NULL, 0}
};

DEFAPI(void) constQLibraryInfo(CTX ctx, knh_class_t cid, const knh_LoaderAPI_t *kapi) {
	kapi->loadClassIntConst(ctx, cid, QLibraryInfoConstInt);
}
