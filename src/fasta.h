#ifndef PYFASTX_FASTA_H
#define PYFASTX_FASTA_H
#include "Python.h"
#include "stdint.h"
#include "zlib.h"
#include "kseq.h"
#include "zran.h"
#include "index.h"
#include "sqlite3.h"

//make sequence iterator
typedef struct {
	PyObject_HEAD

	//fasta or fastq file path and name
	char* file_name;

	//always output uppercase sequence
	uint8_t uppercase;

	//total sequence counts
	uint32_t seq_counts;

	//total sequence length (bp)
	uint64_t seq_length;

	//if build_index is True means has index
	uint8_t has_index;

	//current iter sequence id
	//uint32_t iter_id;

	//cursor for iteration
	sqlite3_stmt *iter_stmt;

	//index for fast random access to sequence
	pyfastx_Index* index;

} pyfastx_Fasta;

extern PyTypeObject pyfastx_FastaType;

void pyfastx_calc_fasta_attrs(pyfastx_Fasta *self);
void pyfastx_fasta_calc_composition(pyfastx_Fasta *self);
void pyfastx_fasta_dealloc(pyfastx_Fasta *self);
int pyfastx_fasta_length(pyfastx_Fasta *self);


PyObject *pyfastx_fasta_new(PyTypeObject *type, PyObject *args, PyObject *kwargs);
PyObject *pyfastx_fasta_iter(pyfastx_Fasta *self);
PyObject *pyfastx_fasta_next(pyfastx_Fasta *self);
PyObject *pyfastx_fasta_repr(pyfastx_Fasta *self);
PyObject *pyfastx_fasta_build_index(pyfastx_Fasta *self);
PyObject *pyfastx_fasta_rebuild_index(pyfastx_Fasta *self);
PyObject *pyfastx_fasta_subscript(pyfastx_Fasta *self, PyObject *item);
PyObject *pyfastx_fasta_fetch(pyfastx_Fasta *self, PyObject *args, PyObject *kwargs);
PyObject *pyfastx_fasta_count(pyfastx_Fasta *self, PyObject *args);
PyObject *pyfastx_fasta_nl(pyfastx_Fasta *self, PyObject *args);
PyObject *pyfastx_fasta_longest(pyfastx_Fasta *self, void* closure);
PyObject *pyfastx_fasta_shortest(pyfastx_Fasta *self, void* closure);
PyObject *pyfastx_fasta_mean(pyfastx_Fasta *self, void* closure);
PyObject *pyfastx_fasta_median(pyfastx_Fasta *self, void* closure);

#endif