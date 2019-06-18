#define ISVISIBLE(C)            ((C->tags & C->mon->tagset[C->mon->seltags]))
Client *
nextc(Client *c) {
	for(; c && !ISVISIBLE(c); c = c->next);
	return c;
}

static Client *
prevc(Client *c) {
	Client *p, *r;

	for(p = selmon->clients, r = NULL; c && p && p != c; p = p->next)
		if(!p->isfloating && ISVISIBLE(p))
			r = p;
	return r;
}

static void
pushup(const Arg *arg) {
	Client *sel = selmon->sel;
	Client *c;

	if(!sel || (sel->isfloating && !arg->f))
		return;
	if((c = prevc(sel))) {
		/* attach before c */
		detach(sel);
		sel->next = c;
		if(selmon->clients == c)
			selmon->clients = sel;
		else {
			for(c = selmon->clients; c->next != sel->next; c = c->next);
			c->next = sel;
		}
        focus(sel);
        arrange(selmon);
	}
}

static void
pushdown(const Arg *arg) {
	Client *sel = selmon->sel;
	Client *c;

	if(!sel || (sel->isfloating && !arg->f))
		return;
	if((c = nextc(sel->next))) {
		/* attach after c */
		detach(sel);
		sel->next = c->next;
		c->next = sel;
        focus(sel);
        arrange(selmon);
	}
}
