void
persistmonitorstate(Monitor *m)
{
	Client *c;
	unsigned int i;

	setmonitortags(m);
	setmonitorfields(m);

	/* Set client atoms */
	for (i = 1, c = m->clients; c; c = c->next, ++i) {
		c->idx = i;
		persistclientstate(c);
	}
}

int
restoremonitorstate(Monitor *m)
{
	return getmonitortags(m) | getmonitorfields(m);
}

void
persistclientstate(Client *c)
{
	setclienttags(c);
	setclientfields(c);
}

int
restoreclientstate(Client *c)
{
	return getclienttags(c)
		| getclientfields(c)
	;
}

void setmonitorfields(Monitor *m)
{
	char atom[22] = {0};
	Atom monitor_fields;
	unsigned int flextile_deluxe_bitmask;

	sprintf(atom, "_DWM_MONITOR_FIELDS_%u", m->num);
	monitor_fields = XInternAtom(dpy, atom, False);

	/* Perists workspace information in 32 bits laid out like this:
	 *
	 * |0|0000|0|0000|0000|0000|0000|0000|000|000
	 * | |    | |    |    |    |    |    |   |-- nmaster
	 * | |    | |    |    |    |    |    |-- nstack
	 * | |    | |    |    |    |    |-- layout
	 * | |    | |    |    |    |-- flextile LAYOUT (split)
	 * | |    | |    |    |-- flextile MASTER
	 * | |    | |    |-- flextile STACK1
	 * | |    | |-- flextile STACK2
	 * | |    |-- flextile mirror layout (indicated by negative layout)
	 * | |
	 * | |-- reserved
	 * |-- showbar
	 */
	flextile_deluxe_bitmask = (m->nstack & 0x7) << 3;
	if (m->lt[m->sellt]->arrange == flextile) {
		flextile_deluxe_bitmask |=
			(abs(m->ltaxis[LAYOUT]) & 0xF) << 10 |
			(m->ltaxis[MASTER] & 0xF) << 14 |
			(m->ltaxis[STACK]  & 0xF) << 18 |
			(m->ltaxis[STACK2] & 0xF) << 22 |
			(m->ltaxis[LAYOUT] < 0 ? 1 : 0) << 24;
	}
	uint32_t data[] = {
		flextile_deluxe_bitmask |
		(m->nmaster & 0x7) |
		(getlayoutindex(m->lt[m->sellt]) & 0xF) << 6 |
		m->showbar << 31
	};

	XChangeProperty(dpy, root, monitor_fields, XA_CARDINAL, 32, PropModeReplace,
		(unsigned char *)data, 1);
}

int
getlayoutindex(const Layout *layout)
{
	int i;

	for (i = 0; i < LENGTH(layouts) && &layouts[i] != layout; i++);
	if (i == LENGTH(layouts))
		i = 0;
	return i;
}

int
getmonitorfields(Monitor *m)
{
	int di, layout_index;
	unsigned long dl, nitems;
	unsigned char *p = NULL;
	char atom[22] = {0};
	Atom da, state = None;

	sprintf(atom, "_DWM_MONITOR_FIELDS_%u", m->num);
	Atom dwm_monitor = XInternAtom(dpy, atom, False);
	if (!dwm_monitor)
		return 0;

	if (!(XGetWindowProperty(dpy, root, dwm_monitor, 0L, sizeof dl,
			False, AnyPropertyType, &da, &di, &nitems, &dl, &p) == Success && p)) {
		return 0;
	}

	if (nitems) {
		state = *(Atom *)p;

		/* See bit layout in the persistmonitorstate function */
		m->nmaster = state & 0x7;
		m->nstack = (state >> 3) & 0x7;
		layout_index = (state >> 6) & 0xF;
		if (layout_index < LENGTH(layouts))
			m->lt[m->sellt] = &layouts[layout_index];
		if (m->lt[m->sellt]->arrange == flextile) {
			m->ltaxis[LAYOUT] = (state >> 10) & 0xF;
			m->ltaxis[MASTER] = (state >> 14) & 0xF;
			m->ltaxis[STACK]  = (state >> 18) & 0xF;
			m->ltaxis[STACK2] = (state >> 22) & 0xF;
		}
		m->showbar = (state >> 31) & 0x1;
	}

	XFree(p);
	return 1;
}

void
setmonitortags(Monitor *m)
{
	char atom[22] = {0};
	Atom monitor_tags;

	sprintf(atom, "_DWM_MONITOR_TAGS_%u", m->num);
	monitor_tags = XInternAtom(dpy, atom, False);

	uint32_t data[] = { m->tagset[m->seltags] };
	XChangeProperty(dpy, root, monitor_tags, XA_CARDINAL, 32, PropModeReplace, (unsigned char *)data, 1);
}

int
getmonitortags(Monitor *m)
{
	int di;
	unsigned long dl, nitems;
	unsigned char *p = NULL;
	char atom[22] = {0};
	Atom da, monitor_tags = None, tags;

	sprintf(atom, "_DWM_MONITOR_TAGS_%u", m->num);
	monitor_tags = XInternAtom(dpy, atom, False);

	if (!(XGetWindowProperty(dpy, root, monitor_tags, 0L, sizeof dl,
			False, AnyPropertyType, &da, &di, &nitems, &dl, &p) == Success && p)) {
		return 0;
	}

	if (nitems) {
		tags = *(Atom *)p;
		m->tagset[m->seltags] = tags & TAGMASK;
	}

	XFree(p);
	return 1;
}

void
setclientfields(Client *c)
{
	/* Perists client information in 32 bits laid out like this:
	 *
	 * |00000000|00000|0|0|0|0|0|0|0|0|00000000|000
	 * |        |     | | | | | | | | |        |-- monitor index
	 * |        |     | | | | | | | | |-- client index
	 * |        |     | | | | | | | |-- isfloating
	 * |        |     | | | | | | |-- ispermanent
	 * |        |     | | | | | |-- isterminal
	 * |        |     | | | | |-- noswallow
	 * |        |     | | | |-- issteam
	 * |        |     | | |-- issticky
	 * |        |     | |-- fakefullscreen
	 * |        |     |-- isfreesize
	 * |        |
	 * |        |-- reserved
	 * |-- scratchkey (for scratchpads)
	 */
	uint32_t data[] = {
		(c->mon->num & 0x7)
		| (c->idx & 0xFF) << 3
		| (c->isfloating & 0x1) << 11
		| (c->issticky & 0x1) << 16
	};
	XChangeProperty(dpy, c->win, clientatom[ClientFields], XA_CARDINAL, 32, PropModeReplace, (unsigned char *)data, 1);
}

int
getclientfields(Client *c)
{
	Monitor *m;
	Atom fields = getatomprop(c, clientatom[ClientFields], AnyPropertyType);
	if (fields == None)
		return 0;

	/* See bit layout in the setclientfields function */
	for (m = mons; m; m = m->next)
		if (m->num == (fields & 0x7)) {
			c->mon = m;
			break;
		}
	c->idx = (fields >> 3) & 0xFF;
	c->isfloating = (fields >> 11) & 0x1;
	c->issticky = (fields >> 16) & 0x1;
	return 1;
}

void
setclienttags(Client *c)
{
	uint32_t data[] = { c->tags };
	XChangeProperty(dpy, c->win, clientatom[ClientTags], XA_CARDINAL, 32, PropModeReplace, (unsigned char *)data, 1);
}

int
getclienttags(Client *c)
{
	Atom tags = getatomprop(c, clientatom[ClientTags], AnyPropertyType);
	if (tags == None)
		return 0;

	c->tags = tags & TAGMASK;
	return 1;
}

