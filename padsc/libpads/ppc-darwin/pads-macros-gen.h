#ifdef _USE_PROTO
#pragma prototyped
#endif
/*
 * WARNING: GENERATED FILE.  Do not edit this file, edit /Users/kfisher/pads/padsc/libpads/pads.c instead. 
 */

#ifndef __PADS_MACROS_GEN_H__
#define __PADS_MACROS_GEN_H__

/*
 * Some generally useful macros
 * 
 * Kathleen Fisher, Robert Gruber
 * AT&T Labs Research
 */

/* ================================================================================ */
/* MACROS USED BY READ FUNCTIONS */

#define PDCI_READFN_PD_INIT(pads, pd) \
do { \
  Pbase_pd_init_no_err(pd); \
  PDCI_READFN_BEGINLOC(pads, (pd)->loc); \
  PD_PGLX_INIT(pads,pd); \
} while (0) \

#define PDCI_FINISH_TIMESTAMP_READ(m_IN, format_IN, tzone_IN, errcode_IN, just_time_IN) \
do { \
  if (P_Test_Set(*(m_IN))) { \
    time_t       tm; \
    Pbyte       *tmp; \
    char        *tmp_t; \
    time_t       now; \
 \
    PDCI_STR_PRESERVE(s); /* this ensures s.str is null terminated */ \
    now = (just_time_IN) ? 0 : time(NiL); \
    /* tm = tmdate(s->str, (char**)&tmp, NiL); */ \
    tmset(tzone_IN); \
    tm = tmscan(s->str, (char**)&tmp, format_IN, &tmp_t, &now, 0L); \
    if (!tmp_t || *tmp_t || !tmp || *tmp) { \
      PDCI_READFN_BEGINLOC_MINUSK(pads, pd->loc, s->len); \
      PDCI_READFN_ENDLOC_MINUS1(pads, pd->loc); \
      PDCI_READFN_RET_ERRCODE_WARN(whatfn, 0, errcode_IN); \
    } \
    (*res_out) = tm; \
    /* normally we do a tmset(pads->out_zone) before using fmttime, */ \
    /* but here for debugging purposes we output using tzone_IN */  \
    P_DBG4(pads->disc, "%s: converted string %s => %s (secs = %ld)", \
	   whatfn, P_qfmt_str(s), fmttime("%K", (time_t)tm), (long)tm); \
  } \
  return P_OK; \
 } while (0); \
 fatal_alloc_err: \
  PDCI_READFN_RET_ERRCODE_FATAL(whatfn, *m, "Memory alloc error", P_ALLOC_ERR) \

#define PDCI_FINISH_DATE_READ(m_IN, format_IN, tzone_IN, errcode_IN, just_time_IN) \
do { \
  if (P_Test_Set(*(m_IN))) { \
    time_t       tm; \
    Pbyte       *tmp; \
    char        *tmp_t; \
    time_t       now; \
    Tm_t        *struct_tm_ptr; \
 \
    PDCI_STR_PRESERVE(s); /* this ensures s.str is null terminated */ \
    now = (just_time_IN) ? 0 : time(NiL); \
    /* tm = tmdate(s->str, (char**)&tmp, NiL); */ \
    tmset(tzone_IN); \
    tm = tmscan(s->str, (char**)&tmp, format_IN, &tmp_t, &now, 0L); \
    if (!tmp_t || *tmp_t || !tmp || *tmp) { \
      PDCI_READFN_BEGINLOC_MINUSK(pads, pd->loc, s->len); \
      PDCI_READFN_ENDLOC_MINUS1(pads, pd->loc); \
      PDCI_READFN_RET_ERRCODE_WARN(whatfn, 0, errcode_IN); \
    } \
    /* replace time portion with midnight */ \
    struct_tm_ptr = tmmake(&tm); \
    struct_tm_ptr->tm_hour  = 0; \
    struct_tm_ptr->tm_min   = 0; \
    struct_tm_ptr->tm_sec   = 0; \
    tm = tmtime(struct_tm_ptr, 0); \
 \
    (*res_out) = tm; \
    /* normally we do a tmset(pads->out_zone) before using fmttime, */ \
    /* but here for debugging purposes we output using tzone_IN */  \
    P_DBG4(pads->disc, "%s: converted string %s => %s (secs = %ld)", \
	   whatfn, P_qfmt_str(s), fmttime("%K", (time_t)tm), (long)tm); \
  } \
  return P_OK; \
 } while (0); \
 fatal_alloc_err: \
  PDCI_READFN_RET_ERRCODE_FATAL(whatfn, *m, "Memory alloc error", P_ALLOC_ERR) \

#define PDCI_FINISH_TIME_READ(m_IN, format_IN, tzone_IN, errcode_IN, just_time_IN) \
do { \
  if (P_Test_Set(*(m_IN))) { \
    time_t       tm; \
    Pbyte       *tmp; \
    char        *tmp_t; \
    time_t       now; \
    Tm_t        *struct_tm_ptr; \
 \
    PDCI_STR_PRESERVE(s); /* this ensures s.str is null terminated */ \
    now = (just_time_IN) ? 0 : time(NiL); \
    /* tm = tmdate(s->str, (char**)&tmp, NiL); */ \
    tmset(tzone_IN); \
    tm = tmscan(s->str, (char**)&tmp, format_IN, &tmp_t, &now, 0L); \
    if (!tmp_t || *tmp_t || !tmp || *tmp) { \
      PDCI_READFN_BEGINLOC_MINUSK(pads, pd->loc, s->len); \
      PDCI_READFN_ENDLOC_MINUS1(pads, pd->loc); \
      PDCI_READFN_RET_ERRCODE_WARN(whatfn, 0, errcode_IN); \
    } \
    /* replace date portion with 1-jan-1970 */ \
    struct_tm_ptr = tmmake(&tm); \
    struct_tm_ptr->tm_mday  = 1;    /* 1-   */ \
    struct_tm_ptr->tm_mon   = 0;    /* jan- */ \
    struct_tm_ptr->tm_year  = 70;   /* 1970 */ \
    tm = tmtime(struct_tm_ptr, 0); \
 \
    (*res_out) = tm; \
    /* normally we do a tmset(pads->out_zone) before using fmttime, */ \
    /* but here for debugging purposes we output using tzone_IN */  \
    P_DBG4(pads->disc, "%s: converted string %s => %s (secs = %ld)", \
	   whatfn, P_qfmt_str(s), fmttime("%K", (time_t)tm), (long)tm); \
  } \
  return P_OK; \
 } while (0); \
 fatal_alloc_err: \
  PDCI_READFN_RET_ERRCODE_FATAL(whatfn, *m, "Memory alloc error", P_ALLOC_ERR) \

/*
 * Starting alloc size for strings, even if initial string is smaller;
 * saves on later alloc calls when Pstring field is re-used many
 * times with strings of different lengths.
 */ 

#define PDCI_STRING_HINT 8 \
 \

/* Pstring_cstr_copy -- inline version.  Caller must provide fatal_alloc_err target */

#define PDCI_STR_CPY(sIN, bIN, wIN) \
  do { \
    size_t wdth_PDCI_STR_CPY = (wIN); \
    if (!(sIN)->rbuf) { \
      if (!((sIN)->rbuf = RMM_new_rbuf(pads->rmm_nz))) { \
	goto fatal_alloc_err; \
      } \
    } \
    if (RBuf_RESERVE_HINT((sIN)->rbuf, (sIN)->str, char, wdth_PDCI_STR_CPY+1, PDCI_STRING_HINT)) { \
      goto fatal_alloc_err; \
    } \
    memcpy((sIN)->str, bIN, wdth_PDCI_STR_CPY); \
    (sIN)->str[wdth_PDCI_STR_CPY] = 0; \
    (sIN)->len = wdth_PDCI_STR_CPY; \
    /* if ((sIN)->sharing) { P_WARN1(pads->disc, "XXX_REMOVE copy: string %p is no longer sharing", (void*)(sIN)); } */ \
    (sIN)->sharing = 0; \
  } while (0) \

/* copy and convert from ASCII to EBCDIC at same time.  Caller must provide fatal_alloc_err target */

#define PDCI_A2E_STR_CPY(sIN, bIN, wIN) \
  do { \
    int i; \
    size_t wdth_PDCI_A2E_STR_CPY = (wIN); \
    if (!(sIN)->rbuf) { \
      if (!((sIN)->rbuf = RMM_new_rbuf(pads->rmm_nz))) { \
	goto fatal_alloc_err; \
      } \
    } \
    if (RBuf_RESERVE_HINT((sIN)->rbuf, (sIN)->str, char, wdth_PDCI_A2E_STR_CPY+1, PDCI_STRING_HINT)) { \
      goto fatal_alloc_err; \
    } \
    for (i = 0; i < wdth_PDCI_A2E_STR_CPY; i++) { \
      (sIN)->str[i] = P_mod_ae_tab[(int)((bIN)[i])]; \
    } \
    (sIN)->str[wdth_PDCI_A2E_STR_CPY] = 0; \
    (sIN)->len = wdth_PDCI_A2E_STR_CPY; \
    /* if ((sIN)->sharing) { P_WARN1(pads->disc, "XXX_REMOVE copy: string %p is no longer sharing", (void*)(sIN)); } */ \
    (sIN)->sharing = 0; \
  } while (0) \

/* copy and convert from EBCDIC to ASCII at same time.  Caller must provide fatal_alloc_err target */

#define PDCI_E2A_STR_CPY(sIN, bIN, wIN) \
  do { \
    int i; \
    size_t wdth_PDCI_E2A_STR_CPY = (wIN); \
    if (!(sIN)->rbuf) { \
      if (!((sIN)->rbuf = RMM_new_rbuf(pads->rmm_nz))) { \
	goto fatal_alloc_err; \
      } \
    } \
    if (RBuf_RESERVE_HINT((sIN)->rbuf, (sIN)->str, char, wdth_PDCI_E2A_STR_CPY+1, PDCI_STRING_HINT)) { \
      goto fatal_alloc_err; \
    } \
    for (i = 0; i < wdth_PDCI_E2A_STR_CPY; i++) { \
      (sIN)->str[i] = P_mod_ea_tab[(int)((bIN)[i])]; \
    } \
    (sIN)->str[wdth_PDCI_E2A_STR_CPY] = 0; \
    (sIN)->len = wdth_PDCI_E2A_STR_CPY; \
    /* if ((sIN)->sharing) { P_WARN1(pads->disc, "XXX_REMOVE copy: string %p is no longer sharing", (void*)(sIN)); } */ \
    (sIN)->sharing = 0; \
  } while (0) \

/* Fill string s with n copies of c.  Caller must provide fatal_alloc_err target */

#define PDCI_STRFILL(sIN, cIN, nIN) \
  do { \
    if (!(sIN)->rbuf) { \
      if (!((sIN)->rbuf = RMM_new_rbuf(pads->rmm_nz))) { \
	goto fatal_alloc_err; \
      } \
    } \
    if (RBuf_RESERVE_HINT((sIN)->rbuf, (sIN)->str, char, (nIN)+1, PDCI_STRING_HINT)) { \
      goto fatal_alloc_err; \
    } \
    memset((sIN)->str, (cIN), (nIN)); \
    (sIN)->str[nIN] = 0; \
    (sIN)->len = (nIN); \
    /* if ((sIN)->sharing) { P_WARN1(pads->disc, "XXX_REMOVE fill: string %p is no longer sharing", (void*)(sIN)); } */ \
    (sIN)->sharing = 0; \
  } while (0) \

/* Pstring_preserve -- inline version.  Caller must provide fatal_alloc_err target */

#define PDCI_STR_PRESERVE(sIN) \
  do { \
    char *shared_str; \
    /* P_WARN3(pads->disc, "XXX_REMOVE [%s:%d] preserve called on shared string %p", __FILE__, __LINE__, (void*)(sIN)); */ \
    /* if (!(sIN)->sharing) { P_WARN3(pads->disc, "XXX_REMOVE [%s:%d] ... but string %p was not shared",__FILE__, __LINE__, (void*)(sIN)); } */ \
    if ((sIN)->sharing) { \
      shared_str = (sIN)->str; \
      PDCI_STR_CPY((sIN), shared_str, (sIN)->len); \
    } \
  } while (0) \

/* Set up str sharing */

#define PDCI_STR_SHARE(sIN, bIN, wIN) \
  do { \
    (sIN)->str = (char*)(bIN); \
    (sIN)->len = (wIN); \
    (sIN)->sharing = 1; \
    /* P_WARN1(pads->disc, "XXX_REMOVE string %p is now sharing", (void*)(sIN)); */ \
  } while (0) \

/* If P_Test_Set(*(mIN)), point to or copy (depending on pads->disc->copy_strings)
 * the string bIN of width wIN
 * Caller must provide fatal_alloc_err target
 */

#define PDCI_A_STR_SET(mIN, sIN, bIN, wIN) \
  do { \
    if (P_Test_Set(*(mIN))) { \
      if (pads->disc->copy_strings) { \
	PDCI_STR_CPY(sIN, bIN, wIN); \
      } else { \
	PDCI_STR_SHARE(sIN, bIN, wIN); \
      } \
    } \
  } while (0) \

/* If P_Test_Set(*(mIN)), copy string of width wIN.
 * Caller must provide fatal_alloc_err target
 */

#define PDCI_STR_CPY_ON_SET(mIN, sIN, bIN, wIN) \
  do { \
    if (P_Test_Set(*(mIN))) { \
      PDCI_STR_CPY(sIN, bIN, wIN); \
    } \
  } while (0) \

/* If P_Test_Set(*(mIN)), copy (always copy for EBCDIC) the
 * string bIN of width wIN and convert copy to ASCII.
 * Caller must provide fatal_alloc_err target.
 */

#define PDCI_E_STR_SET(mIN, sIN, bIN, wIN) \
  do { \
    if (P_Test_Set(*(mIN))) { \
      PDCI_E2A_STR_CPY(sIN, bIN, wIN); \
    } \
  } while (0) \

/* ----------------------------------------------------------- */
/* The following cases either have a hard or soft goal for max */
/* bytes (a soft goal means it is OK to produce more bytes if  */
/* they happen to be available in the current elt).            */

/* The following has to appear where variables can be declared */

#define PDCI_IO_NEED_BYTES_SETUP_PREAMBLE \
  PDCI_stkElt_t    *tp              = &(pads->stack[pads->top]); \
  Pio_elt_t        *elt             = tp->elt; \
  Pio_elt_t        *keep_elt; \
  Pio_elt_t        *next_elt; \
  Pbyte            *begin; \
  Pbyte            *end; \
  size_t            bytes           = tp->remain; \
  int               eor; \
  int               eof \

/* The following has to appear where variables can be declared */

#define PDCI_IO_NEED_BYTES_SETUP_MATCH \
  PDCI_IO_NEED_BYTES_SETUP_PREAMBLE; \
  int               soft_goal       = 0; \
  size_t            goal_bytes      = pads->disc->match_max; \
  if (!goal_bytes && !pads->disc->io_disc->rec_based) { \
    soft_goal  = 1; \
    goal_bytes = P_BUILTIN_MATCH_MAX; \
  } \

/* The following has to appear where variables can be declared */

#define PDCI_IO_NEED_BYTES_SETUP_SCAN \
  PDCI_IO_NEED_BYTES_SETUP_PREAMBLE; \
  int               soft_goal       = 0; \
  size_t            goal_bytes      = pads->disc->scan_max; \
  if (!goal_bytes && !pads->disc->io_disc->rec_based) { \
    soft_goal  = 1; \
    goal_bytes = P_BUILTIN_SCAN_MAX; \
  } \

/* The following has to appear where variables can be declared */

#define PDCI_IO_NEED_BYTES_SETUP_PANIC \
  PDCI_IO_NEED_BYTES_SETUP_PREAMBLE; \
  int               soft_goal       = 0; \
  size_t            goal_bytes      = pads->disc->panic_max; \
  if (!goal_bytes && !pads->disc->io_disc->rec_based) { \
    soft_goal  = 1; \
    goal_bytes = P_BUILTIN_PANIC_MAX; \
  } \

/* The following has to appear where variables can be declared */

#define PDCI_IO_NEED_BYTES_SETUP_SCAN_OR_PANIC(panic) \
  PDCI_IO_NEED_BYTES_SETUP_PREAMBLE; \
  int               soft_goal       = 0; \
  size_t            goal_bytes; \
  if (panic) { \
    goal_bytes = pads->disc->panic_max; \
    if (!goal_bytes && !pads->disc->io_disc->rec_based) { \
      soft_goal  = 1; \
      goal_bytes = P_BUILTIN_PANIC_MAX; \
    } \
  } else { \
    goal_bytes = pads->disc->scan_max; \
    if (!goal_bytes && !pads->disc->io_disc->rec_based) { \
      soft_goal  = 1; \
      goal_bytes = P_BUILTIN_SCAN_MAX; \
    } \
  } \

/* The following has to appear where variables can be declared */

#define PDCI_IO_NEED_BYTES_SETUP_NUMERIC \
  PDCI_IO_NEED_BYTES_SETUP_PREAMBLE; \
  int               soft_goal       = 0; \
  size_t            goal_bytes      = pads->disc->numeric_max; \
  if (!goal_bytes && !pads->disc->io_disc->rec_based) { \
    soft_goal  = 1; \
    goal_bytes = P_BUILTIN_NUMERIC_MAX; \
  } \

/* The IOerrorSTMT statement must be/include goto or return; it */
/* is assumed NOT to fall through.  Further, begin/end/etc are  */
/* NOT set properly if IOerrorSTMT is used.                     */

#define PDCI_IO_NEED_BYTES(IOerrorSTMT) \
do { \
  while (!(elt->eor|elt->eof) && (soft_goal || !goal_bytes || bytes < goal_bytes)) { \
    /* try for more bytes */ \
    if (elt->next != pads->head) { /* the easy case */ \
      elt = elt->next; \
      bytes += elt->len; \
      continue; \
    } \
    /* elt->next is pads->head, getting more bytes requires use of read_fn */ \
    /* if soft goal and it has been hit, stop now */ \
    if (soft_goal && (bytes >= goal_bytes)) break; \
    keep_elt = pads->stack[0].elt; \
    if (P_ERR == pads->disc->io_disc->read_fn(pads, pads->disc->io_disc, keep_elt, &next_elt)) { \
      IOerrorSTMT; \
    } \
    elt = elt->next; \
    bytes += elt->len; \
  } \
  begin = tp->elt->end - tp->remain; \
  /* either we hit eor or eof, or we found >= goal_bytes bytes */ \
  if (soft_goal && (bytes > goal_bytes)) { \
    /* adjust goal upwards rather than not returning all the bytes we found */ \
    goal_bytes = bytes; \
  } \
  if (!goal_bytes || elt->eor) { \
    /* Goal was eor and we got eor|eof, OR goal was set but we found eor first, \
     * which is also acceptable as a goal. Either way, include all bytes found. \
     * Since this is record-based case, set goal > end if !eor \
     */ \
    end = elt->end; \
    eor = elt->eor; \
    eof = elt->eof; \
  } else { \
    /* had hard or soft goal_bytes (> 0) and eor not found.  eof may have been found */ \
    eor = 0; \
    if (bytes > goal_bytes) { \
      /* found more than enough (end will be prior to any eof byte) */ \
      end  = begin + goal_bytes; \
      eof  = 0; \
    } else if (bytes == goal_bytes) { \
      /* found exactly enough (not sure if end is at eof) */ \
      end  = begin + goal_bytes; \
      eof  = (end == elt->end) ? elt->eof : 0; \
    } else { \
      /* did not find enough (must have hit eof) */ \
      end  = elt->end; \
      eof  = 1; \
    } \
  } \
} while (0) \

/* ----------------------------------------------------------- */
/* For the case where we specify a specific max bytes          */
/* greater than zero, which is a hard limit, or zero, which    */
/* uses eor as the hard limit (must be record-based to use 0). */ 

/* The following has to appear where variables can be declared */

#define PDCI_IO_NEED_BYTES_SETUP_SPECIFIC \
  PDCI_IO_NEED_BYTES_SETUP_PREAMBLE \

/* The IOerrorSTMT statement must be/include goto or return; it */
/* is assumed NOT to fall through.  Further, begin/end/etc are  */
/* NOT set properly if IOerrorSTMT is used.                     */

#define PDCI_IO_NEED_BYTES_SPECIFIC(specific, IOerrorSTMT) \
do { \
  size_t goal_bytes = specific; \
  if (goal_bytes == 0) { \
    while (!(elt->eor|elt->eof)) { \
      /* try for more bytes */ \
      if (elt->next != pads->head) { /* the easy case */ \
	elt = elt->next; \
	bytes += elt->len; \
	continue; \
      } \
      /* elt->next is pads->head, getting more bytes requires use of read_fn */ \
      keep_elt = pads->stack[0].elt; \
      if (P_ERR == pads->disc->io_disc->read_fn(pads, pads->disc->io_disc, keep_elt, &next_elt)) { \
	IOerrorSTMT; \
      } \
      elt = elt->next; \
      bytes += elt->len; \
    } \
    begin = tp->elt->end - tp->remain; \
    end  = elt->end; \
    eor  = elt->eor; \
    eof  = elt->eof; \
  } else { \
    /* goal_bytes > 0 */ \
    while (!(elt->eor|elt->eof) && (bytes < goal_bytes)) { \
      /* try for more bytes */ \
      if (elt->next != pads->head) { /* the easy case */ \
	elt = elt->next; \
	bytes += elt->len; \
	continue; \
      } \
      /* elt->next is pads->head, getting more bytes requires use of read_fn */ \
      keep_elt = pads->stack[0].elt; \
      if (P_ERR == pads->disc->io_disc->read_fn(pads, pads->disc->io_disc, keep_elt, &next_elt)) { \
	IOerrorSTMT; \
      } \
      elt = elt->next; \
      bytes += elt->len; \
    } \
    begin = tp->elt->end - tp->remain; \
    if (bytes > goal_bytes) { \
      /* found more than enough (end will be prior any eor/eof) */ \
      end = begin + goal_bytes; \
      eor  = 0; \
      eof  = 0; \
    } else if (bytes == goal_bytes) { \
      /* may have hit eor or eof */ \
      end = begin + goal_bytes; \
      eor  = elt->eor; \
      eof  = elt->eof; \
    } else { \
      /* def hit eor or eof.  produce as many bytes as available */ \
      end  = elt->end; \
      eor  = elt->eor; \
      eof  = elt->eof; \
    } \
  } \
} while (0) \

/* ---------------------------------------------------------------- */
/* For the case where we need exactly K bytes or there is an error. */

/* The following has to appear where variables can be declared */

#define PDCI_IO_NEED_K_BYTES_SETUP \
  PDCI_stkElt_t    *tp              = &(pads->stack[pads->top]); \
  Pio_elt_t        *elt             = tp->elt; \
  Pio_elt_t        *keep_elt; \
  Pio_elt_t        *next_elt; \
  Pbyte            *begin; \
  Pbyte            *end; \
  size_t            bytes           = tp->remain; \
  int               eor; \
  int               eof \

/* The IOerrorSTMT statement must be/include goto or return; it */
/* is assumed NOT to fall through.  Further, begin/end are NOT  */
/* set properly if IOerrorSTMT is used.                         */

#define PDCI_IO_NEED_K_BYTES(kIN, IOerrorSTMT) \
do { \
  while (!(elt->eor|elt->eof) && (bytes < (kIN))) { \
    /* try for more bytes */ \
    if (elt->next != pads->head) { /* the easy case */ \
      elt = elt->next; \
      bytes += elt->len; \
      continue; \
    } \
    /* elt->next is pads->head, getting more bytes requires use of read_fn */ \
    keep_elt = pads->stack[0].elt; \
    if (P_ERR == pads->disc->io_disc->read_fn(pads, pads->disc->io_disc, keep_elt, &next_elt)) { \
      IOerrorSTMT; \
    } \
    elt = elt->next; \
    bytes += elt->len; \
  } \
  /* either we hit eor or eof, or we found >= kIN bytes */ \
  begin = tp->elt->end - tp->remain; \
  if (bytes > (kIN)) { \
    end = begin + (kIN); \
    eor = 0; \
    eof = 0; \
  } else { \
    end = elt->end; \
    eor = elt->eor; \
    eof = elt->eof; \
  } \
} while (0) \

/* ----------------------------------------------------------------- */
/* Move forward by K bytes; should be able to move forward K without */
/* reading new bytes or advancing past EOR/EOF.                      */
/* N.B. Assumes one of the NEED_BYTES macros has been used and that  */
/*      the variables introduced by the SETUP macro are in scope.    */

/* The IOerrorSTMT statement must be/include goto or return; it */
/* is assumed NOT to fall through.                              */

#define PDCI_IO_FORWARD(num_bytes, IOerrorSTMT) \
do { \
  size_t todo = num_bytes; \
  while (todo > 0) { \
    if (tp->remain == 0) { \
      if (tp->elt->eor|tp->elt->eof) { \
	P_FATAL(pads->disc, "Internal error, PDCI_IO_FORWARD hit EOR or EOF"); \
      } \
      if (tp->elt->next == pads->head) { \
	P_FATAL(pads->disc, "Internal error, PDCI_IO_FORWARD would need to read bytes from io stream"); \
      } \
      tp->elt = tp->elt->next; \
      tp->remain = tp->elt->len; \
      continue; \
    } \
    if (todo <= tp->remain) { \
      tp->remain -= todo; \
      todo = 0; \
      break; \
    } \
    /* current IO rec gets us partway */ \
    todo -= tp->remain; \
    tp->remain = 0; \
  } \
  /* success */ \
  if (!tp->remain && !(tp->elt->eor|tp->elt->eof)) { \
    /* at end of a non-EOR, non-EOF elt: advance now */ \
    if (tp->elt->next != pads->head) { \
      tp->elt = tp->elt->next; \
      tp->remain = tp->elt->len; \
    } else { \
      /* need to read some data -- use IO disc read_fn */ \
      keep_elt = pads->stack[0].elt; \
      if (P_ERR == pads->disc->io_disc->read_fn(pads, pads->disc->io_disc, keep_elt, &next_elt)) { \
	tp->elt = P_LAST_ELT(pads->head); /* IO disc may have added eof elt */ \
	tp->remain = 0; \
	IOerrorSTMT; \
      } \
      tp->elt = next_elt; \
      tp->remain = tp->elt->len; \
    } \
  } \
} while (0) \
 \
/* ================================================================================ */ \
/* MACROS USED BY ACCUM FUNCTIONS */ \
  \
/* Useful constants */ \
 \

#define PDCI_HALFMIN_INT64   -4611686018427387904LL \

#define PDCI_HALFMAX_INT64    4611686018427387903LL \

#define PDCI_HALFMAX_UINT64   9223372036854775807ULL \

#define PDCI_LARGE_NEG_DBL   -4611686018427387904.0 \

#define PDCI_LARGE_POS_DBL    4611686018427387903.0 \

/* Fold Points : when should the running int64 / uint64 sum be folded into the average? */

#define PDCI_FOLD_MIN_INT8    -9223372036854775680LL  /* P_MIN_INT64 - P_MIN_INT8  */ \

#define PDCI_FOLD_MAX_INT8     9223372036854775680LL  /* P_MAX_INT64 - P_MAX_INT8  */ \

#define PDCI_FOLD_MIN_INT16   -9223372036854743040LL  /* P_MIN_INT64 - P_MIN_INT16 */ \

#define PDCI_FOLD_MAX_INT16    9223372036854743040LL  /* P_MAX_INT64 - P_MAX_INT16 */ \

#define PDCI_FOLD_MIN_INT32   -9223372034707292160LL  /* P_MIN_INT64 - P_MIN_INT32 */ \

#define PDCI_FOLD_MAX_INT32    9223372034707292160LL  /* P_MAX_INT64 - P_MAX_INT32 */ \
 \

#define PDCI_FOLD_MAX_UINT8   18446744073709551488ULL  /* P_MAX_UINT64 - P_MAX_UINT8  */ \

#define PDCI_FOLD_MAX_UINT16  18446744073709518848ULL  /* P_MAX_UINT64 - P_MAX_UINT16 */ \

#define PDCI_FOLD_MAX_UINT32  18446744069414584320ULL  /* P_MAX_UINT64 - P_MAX_UINT32 */ \

/* Macros that test whether folding should occur, given new val v and running sum s */

#define PDCI_FOLDTEST_INT8(v, s)  (((s) < PDCI_FOLD_MIN_INT8)  || ((s) > PDCI_FOLD_MAX_INT8)) \

#define PDCI_FOLDTEST_INT16(v, s) (((s) < PDCI_FOLD_MIN_INT16) || ((s) > PDCI_FOLD_MAX_INT16)) \

#define PDCI_FOLDTEST_INT32(v, s) (((s) < PDCI_FOLD_MIN_INT32) || ((s) > PDCI_FOLD_MAX_INT32)) \

#define PDCI_FOLDTEST_INT32(v, s) (((s) < PDCI_FOLD_MIN_INT32) || ((s) > PDCI_FOLD_MAX_INT32)) \

#define PDCI_FOLDTEST_INT64(v, s) ( (((s) < 0) && ((v) < PDCI_HALFMIN_INT64)) || \
				   (((v) < 0) && ((s) < PDCI_HALFMIN_INT64)) || \
				   (((s) > 0) && ((v) > PDCI_HALFMAX_INT64)) || \
				   (((v) > 0) && ((s) > PDCI_HALFMAX_INT64)) ) \

#define PDCI_FOLDTEST_UINT8(v, s)  ((s) > PDCI_FOLD_MAX_UINT8) \

#define PDCI_FOLDTEST_UINT16(v, s) ((s) > PDCI_FOLD_MAX_UINT16) \

#define PDCI_FOLDTEST_UINT32(v, s) ((s) > PDCI_FOLD_MAX_UINT32) \

#define PDCI_FOLDTEST_UINT64(v, s) ( ((s) > PDCI_HALFMAX_UINT64) || ((v) > PDCI_HALFMAX_UINT64) ) \

/* ================================================================================ */
/* DOUBLY-LINKED LIST HELPER MACROS */

#define P_SOME_ELTS(head) ((head)->next != (head)) \

#define P_FIRST_ELT(head) ((head)->next) \

#define P_LAST_ELT(head)  ((head)->prev) \

#define P_REMOVE_ELT(elt) \
  do { \
    (elt)->prev->next = (elt)->next; \
    (elt)->next->prev = (elt)->prev; \
  } while (0) \

#define P_APPEND_ELT(head, elt) \
  do { \
    (elt)->prev = (head)->prev; \
    (elt)->next = (head); \
    (elt)->prev->next = (elt); \
    (elt)->next->prev = (elt); \
  } while (0) \

#define P_PREPEND_ELT(head, elt) \
  do { \
    (elt)->prev = (head); \
    (elt)->next = (head)->next; \
    (elt)->prev->next = (elt); \
    (elt)->next->prev = (elt); \
  } while (0) \

/* ================================================================================ */
/* WRITE FUNCTION HELPER MACROS */

#define PDCI_WFMT_INT_WRITE(writelen, iostr, wfmt, width, t) \
  do { \
    writelen = sfprintf(iostr, wfmt, ((t < 0) ? width-1 : width), t); \
  } while (0) \

#define PDCI_WFMT_UINT_WRITE(writelen, iostr, wfmt, width, t) \
  do { \
    writelen = sfprintf(iostr, wfmt, width, t); \
  } while (0) \

#define PDCI_FMT_INT_WRITE(writelen, iostr, fmt, t) \
  do { \
    writelen = sfprintf(iostr, fmt, t); \
  } while (0) \

#define PDCI_FMT_UINT_WRITE(writelen, iostr, fmt, t) \
  do { \
    writelen = sfprintf(iostr, fmt, t); \
  } while (0) \

/* sfprintf workaround for signed int1 vals */

#define PDCI_WFMT_INT1_WRITE(writelen, iostr, wfmt, width, t) \
  do { \
    Pint32 t_subst = t; \
    writelen = sfprintf(iostr, "%0.*I4d", ((t < 0) ? width-1 : width), t_subst); \
  } while (0) \

/* sfprintf workaround for signed int1 vals */

#define PDCI_FMT_INT1_WRITE(writelen, iostr, fmt, t) \
  do { \
    Pint32 t_subst = t; \
    writelen = sfprintf(iostr, "%I4d", t_subst); \
  } while (0) \

#define PDCI_FMT_FLOAT_WRITE(writelen, iostr, fmt, t) \
  do { \
    writelen = sfprintf(iostr, fmt, t); \
  } while (0) \

#define PDCI_WFMT_FLOAT_WRITE(writelen, iostr, wfmt, width, t) \
  do { \
    writelen = sfprintf(iostr, wfmt, ((t < 0) ? width-1 : width), t); \
  } while (0) \

#define PDCI_BASELIT_XML_OUT(sfprintf_prefix, io, tag, def_tag, indent, outfmt, outval) \
  do { \
    if (!tag) { tag = def_tag; } \
    indent = (indent > 128) ? 128 : indent; \
    sfprintf_prefix sfprintf(io, "%.*s<%s><val>" outfmt "</val></%s>\n", indent, PDCI_spaces, tag, outval, tag); \
  } while (0) \

/* assumes variables io, tag, indent are in scope */

#define PDCI_BASELIT_XML_OUT2IO(def_tag, outfmt, outval) \
  PDCI_BASELIT_XML_OUT(return, io, tag, def_tag, indent, outfmt, outval) \

/* assumes variables writelen, buf, buf_full, buf_len, pads, tag, indent are in scope */

#define PDCI_BASELIT_XML_OUT2BUF(def_tag, outfmt, outval) \
  do { \
    PDCI_sfstr_seek2zero(pads->tmp3); \
    PDCI_BASELIT_XML_OUT(writelen = , pads->tmp3, tag, def_tag, indent, outfmt, outval); \
    if (writelen <= 0) { \
      return -1; \
    } \
    if (writelen > buf_len) { \
      (*buf_full) = 1; \
      return -1; \
    } \
    memcpy(buf, PDCI_sfstr_use(pads->tmp3), writelen); \
    return writelen; \
  } while (0) \

/* AJF - this definition is available from pcgen-macros.h and if you have to update it, it's nice
 * to only have to do it in one place.

 * #define PSTATE_NERR_ERRCODE_FMT "<pstate>%s</pstate><nerr>%I4u</nerr><errCode>%s</errCode>"  \
 */ \

#define LOC_FMT "<loc><b><num>%lld</num><byte>%lld</byte></b><e><num>%lld</num><byte>%lld</byte></e></loc>" \

#define PDCI_BASEVAL_XML_OUT(sfprintf_prefix, io, tag, def_tag, indent, pd, outfmt, outval) \
  do { \
    if (!tag) { tag = def_tag; } \
    indent = (indent > 128) ? 128 : indent; \
    if ((pd)->errCode == P_NO_ERR) { /* value, no errors */ \
      sfprintf_prefix sfprintf(io, "%.*s<%s><val>" outfmt "</val></%s>\n",  \
			       indent,  \
			       PDCI_spaces,  \
			       tag,  \
			       outval,  \
			       tag); \
    } else if ((pd)->errCode < 100) { /* no value, no location */ \
      sfprintf_prefix sfprintf(io, "%.*s<%s><pd>" PSTATE_NERR_ERRCODE_FMT "</pd></%s>\n", \
			       indent,  \
			       PDCI_spaces,  \
			       tag,  \
			       P_pstate2str((pd)->pstate),  \
			       (pd)->nerr,  \
			       P_errCode2str((pd)->errCode),  \
			       tag); \
    } else if ((pd)->errCode == P_USER_CONSTRAINT_VIOLATION) { /* value and location */ \
      sfprintf_prefix sfprintf(io, "%.*s<%s><val>" outfmt "</val>\n%.*s<pd>" PSTATE_NERR_ERRCODE_FMT "\n%.*s" LOC_FMT "</pd></%s>\n", \
			       indent,  \
			       PDCI_spaces,  \
			       tag, 			       	 \
			       outval, \
 			       indent,  \
			       PDCI_spaces,  \
			       P_pstate2str((pd)->pstate),  \
			       (pd)->nerr,  \
	                       P_errCode2str((pd)->errCode), \
			       indent,  \
			       PDCI_spaces,  \
			       (long long)(pd)->loc.b.num, (long long)(pd)->loc.b.byte,  \
			       (long long)(pd)->loc.e.num, (long long)(pd)->loc.e.byte,  \
			       tag); \
    } else { /* no value, location */ \
      sfprintf_prefix sfprintf(io, "%.*s<%s><pd>" PSTATE_NERR_ERRCODE_FMT LOC_FMT "</pd></%s>\n", \
			       indent,  \
			       PDCI_spaces,  \
			       tag,  \
			       P_pstate2str((pd)->pstate),  \
			       (pd)->nerr,  \
			       P_errCode2str((pd)->errCode), \
			       (long long)(pd)->loc.b.num, (long long)(pd)->loc.b.byte,  \
			       (long long)(pd)->loc.e.num, (long long)(pd)->loc.e.byte,  \
			       tag); \
    } \
  } while (0) \

/* assumes variables io, tag, indent, pd are in scope */

#define PDCI_BASEVAL_XML_OUT2IO(def_tag, outfmt, outval) \
  PDCI_BASEVAL_XML_OUT(return, io, tag, def_tag, indent, pd, outfmt, outval) \

/* assumes variables writelen, buf, buf_full, buf_len, pads, tag, indent, pd are in scope */

#define PDCI_BASEVAL_XML_OUT2BUF(def_tag, outfmt, outval) \
  do { \
    PDCI_sfstr_seek2zero(pads->tmp3); \
    PDCI_BASEVAL_XML_OUT(writelen = , pads->tmp3, tag, def_tag, indent, pd, outfmt, outval); \
    if (writelen <= 0) { \
      return -1; \
    } \
    if (writelen > buf_len) { \
      (*buf_full) = 1; \
      return -1; \
    } \
    memcpy(buf, PDCI_sfstr_use(pads->tmp3), writelen); \
    return writelen; \
  } while (0) \

#endif  /*  __PADS_MACROS_GEN_H__  */
