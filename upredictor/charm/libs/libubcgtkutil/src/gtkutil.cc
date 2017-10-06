#include "gtkutil.h"
#include "ExternalUpdate.h"

gboolean gtkupdate(gpointer data) {
	((ExternalUpdate *) data)->update();
	return TRUE;
}
