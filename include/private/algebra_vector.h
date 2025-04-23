#ifndef ALGEBRA_VECTOR_H
#define ALGEBRA_VECTOR_H

#include "osqp_api_types.h"

#include "glob_opts.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  OSQPVector[fi] types.  Not defined here since it
 *  is implementation-specific
 */

/* integer valued vectors */
typedef struct OSQPVectori_ OSQPVectori;

/* float valued vectors*/
typedef struct OSQPVectorf_ OSQPVectorf;


/* VECTOR FUNCTIONS ----------------------------------------------------------*/

# ifndef OSQP_EMBEDDED_MODE

OSQP_API OSQPInt OSQPVectorf_is_eq(const OSQPVectorf* A,
                          const OSQPVectorf* B,
                          OSQPFloat          tol);

/* malloc/calloc for floats and ints (USES MALLOC/CALLOC) */
OSQP_API OSQPVectorf* OSQPVectorf_malloc(OSQPInt length);
OSQP_API OSQPVectorf* OSQPVectorf_calloc(OSQPInt length);
OSQP_API OSQPVectori* OSQPVectori_malloc(OSQPInt length);
OSQP_API OSQPVectori* OSQPVectori_calloc(OSQPInt length);

/* Return a float vector using a raw array as input (Uses MALLOC) */
OSQP_API OSQPVectorf* OSQPVectorf_new(const OSQPFloat* a,
                             OSQPInt          length);

/* Return an int vector using a raw array as input (Uses MALLOC) */
OSQP_API OSQPVectori* OSQPVectori_new(const OSQPInt* a,
                             OSQPInt        length);

/* Return a copy of a float vector a as output (Uses MALLOC) */
OSQP_API OSQPVectorf* OSQPVectorf_copy_new(const OSQPVectorf* a);

/* Free a float vector */
OSQP_API void OSQPVectorf_free(OSQPVectorf* a);

/* Free an int vector */
OSQP_API void OSQPVectori_free(OSQPVectori* a);

/*
 * Assign the data from array b to vector A starting at the index given by start.
 */
OSQP_API void OSQPVectorf_subvector_assign(OSQPVectorf* A,
                                  OSQPFloat*   b,
                                  OSQPInt      start,
                                  OSQPInt      length,
                                  OSQPFloat    multiplier);

/*
 * Assign a scalar to vector A starting at the index given by start.
 */
OSQP_API void OSQPVectorf_subvector_assign_scalar(OSQPVectorf* A,
                                  OSQPFloat    sc,
                                  OSQPInt      start,
                                  OSQPInt      length);

OSQP_API OSQPVectorf* OSQPVectorf_subvector_byrows(const OSQPVectorf* A,
                                          const OSQPVectori* rows);

OSQP_API OSQPVectorf* OSQPVectorf_concat(const OSQPVectorf* A,
                                const OSQPVectorf* B);

/* Create subview of a larger vector.  Internal data should not be freed.
 * Behavior is otherwise identical to OSQPVectorf (Uses MALLOC)
 */
OSQP_API OSQPVectorf* OSQPVectorf_view(const OSQPVectorf* a,
                              OSQPInt            head,
                              OSQPInt            length);

/* Points existing subview somewhere else.  (Does not use MALLOC)
 * TODO: Get rid of this function
 */
OSQP_API void OSQPVectorf_view_update(OSQPVectorf* a, const OSQPVectorf* b, OSQPInt head, OSQPInt length);

/* Free a view of a float vector */
OSQP_API void OSQPVectorf_view_free(OSQPVectorf* a);

# endif /* ifndef OSQP_EMBEDDED_MODE */


/* Length of the vector (floats) */
OSQP_API OSQPInt OSQPVectorf_length(const OSQPVectorf* a);

/* Length of the vector (ints) */
OSQP_API OSQPInt OSQPVectori_length(const OSQPVectori* a);

/* Pointer to vector data (floats) */
OSQP_API OSQPFloat* OSQPVectorf_data(const OSQPVectorf* a);

/* Copy a float vector a into another vector b (pre-allocated) */
OSQP_API void OSQPVectorf_copy(OSQPVectorf*       b,
                      const OSQPVectorf* a);

/* Copy an array of floats into a into a vector b (pre-allocated) */
OSQP_API void OSQPVectorf_from_raw(OSQPVectorf*     b,
                          const OSQPFloat* a);

/* copy an array of ints into a into a vector b (pre-allocated) */
OSQP_API void OSQPVectori_from_raw(OSQPVectori*   b,
                          const OSQPInt* a);

/* copy a vector into an array of floats (pre-allocated) */
OSQP_API void OSQPVectorf_to_raw(OSQPFloat*         bv,
                        const OSQPVectorf* a);

/* copy a vector into an array of ints (pre-allocated) */
OSQP_API void OSQPVectori_to_raw(OSQPInt*           bv,
                        const OSQPVectori* a);

/* set float vector to scalar */
OSQP_API void OSQPVectorf_set_scalar(OSQPVectorf* a,
                            OSQPFloat    sc);

/* Set float vector to one of three scalars based on sign of vector of ints */
OSQP_API void OSQPVectorf_set_scalar_conditional(OSQPVectorf*       a,
                                        const OSQPVectori* test,
                                        OSQPFloat          val_if_neg,
                                        OSQPFloat          val_if_zero,
                                        OSQPFloat          val_if_pos);

/**
 * Round any values of a between [-tol, tol] to zero, creating a deadband around 0.
 */
OSQP_API void OSQPVectorf_round_to_zero(OSQPVectorf* a,
                               OSQPFloat    tol);

/* multiply float vector by float */
OSQP_API void OSQPVectorf_mult_scalar(OSQPVectorf* a,
                             OSQPFloat    sc);

/* x = a + b.  Set x == a for x += b. */
OSQP_API void OSQPVectorf_plus(OSQPVectorf*       x,
                      const OSQPVectorf* a,
                      const OSQPVectorf* b);

/* x = a - b.  Set x==a for x -= b. */
OSQP_API void OSQPVectorf_minus(OSQPVectorf*      x,
                      const OSQPVectorf* a,
                      const OSQPVectorf* b);

/* x = sca*a + scb*b.  Set (x == a, sca==1.) for x += scb*b. */
OSQP_API void OSQPVectorf_add_scaled(OSQPVectorf*       x,
                            OSQPFloat          sca,
                            const OSQPVectorf* a,
                            OSQPFloat          scb,
                            const OSQPVectorf* b);

/* x = sca*a + scb*b + scc*c.  Set (x == a, sca==1.) for x += scb*b scc*c. */
OSQP_API void OSQPVectorf_add_scaled3(OSQPVectorf*       x,
                             OSQPFloat          sca,
                             const OSQPVectorf* a,
                             OSQPFloat          scb,
                             const OSQPVectorf* b,
                             OSQPFloat          scc,
                             const OSQPVectorf* c);

/* ||v||_inf */
OSQP_API OSQPFloat OSQPVectorf_norm_inf(const OSQPVectorf* v);

/* ||Sv||_inf */
OSQP_API OSQPFloat OSQPVectorf_scaled_norm_inf(const OSQPVectorf* S,
                                      const OSQPVectorf* v);

/* ||a - b||_inf */
OSQP_API OSQPFloat OSQPVectorf_norm_inf_diff(const OSQPVectorf* a,
                                    const OSQPVectorf* b);

/* ||v||2 */
OSQP_API OSQPFloat OSQPVectorf_norm_2(const OSQPVectorf* v);

/* ||v||1 */
OSQP_API OSQPFloat OSQPVectorf_norm_1(const OSQPVectorf* a);

/* Inner product a'b */
OSQP_API OSQPFloat OSQPVectorf_dot_prod(const OSQPVectorf* a,
                               const OSQPVectorf* b);

/* Inner product a'b, but using only the positive or negative
 * terms in b.  Use sign = 1 for positive terms, sign = -1 for
 * negative terms.  Setting any other value for sign will return
 * the normal dot product
 */
 OSQP_API OSQPFloat OSQPVectorf_dot_prod_signed(const OSQPVectorf* a,
                                      const OSQPVectorf* b,
                                      OSQPInt            sign);

/* Elementwise product a.*b stored in c.  Set c==a for c *= b */
OSQP_API void OSQPVectorf_ew_prod(OSQPVectorf*       c,
                         const OSQPVectorf* a,
                         const OSQPVectorf* b);

/* check l <= u elementwise.  Returns 1 if inequality is true
 * for every element pair in both vectors
 */
OSQP_API OSQPInt OSQPVectorf_all_leq(const OSQPVectorf* l,
                            const OSQPVectorf* u);

/* Elementwise bounding vectors x = min(max(z,l),u)
 * It is acceptable to assign x = z in this call, so
 * that x = min(max(x,l),u) is allowed
 */
OSQP_API void OSQPVectorf_ew_bound_vec(OSQPVectorf*       x,
                              const OSQPVectorf* z,
                              const OSQPVectorf* l,
                              const OSQPVectorf* u);


/* Elementwise projection of y onto the polar recession cone
   of the set [l u].  Values of +/- infval or larger are
   treated as infinite
 */
OSQP_API void OSQPVectorf_project_polar_reccone(OSQPVectorf*       y,
                                       const OSQPVectorf* l,
                                       const OSQPVectorf* u,
                                       OSQPFloat          infval);

/* Elementwise test of whether y is in the polar recession
   cone of the set [l u].  Values of +/- infval or larger are
   treated as infinite.  Values in y within tol of zero are treated
   as zero.
 */
OSQP_API OSQPInt OSQPVectorf_in_reccone(const OSQPVectorf* y,
                               const OSQPVectorf* l,
                               const OSQPVectorf* u,
                               OSQPFloat          infval,
                               OSQPFloat          tol);

# if OSQP_EMBEDDED_MODE != 1

/* Vector elementwise reciprocal b = 1./a (needed for scaling)*/
OSQP_API void OSQPVectorf_ew_reciprocal(OSQPVectorf*       b,
                               const OSQPVectorf* a);

/* elementwise sqrt of the vector elements */
OSQP_API void OSQPVectorf_ew_sqrt(OSQPVectorf* a);

/* Elementwise maximum between vectors c = max(a, b) */
OSQP_API void OSQPVectorf_ew_max_vec(OSQPVectorf*       c,
                            const OSQPVectorf* a,
                            const OSQPVectorf* b);

/* Elementwise minimum between vectors c = min(a, b) */
OSQP_API void OSQPVectorf_ew_min_vec(OSQPVectorf*       c,
                            const OSQPVectorf* a,
                            const OSQPVectorf* b);

/* Elementwise check for constraint type.
   if u[i] - l[i] < tol, iseq[i] = 1 otherwise iseq[i] = 0,
   unless values exceed +/- infval, in which case marked
   as iseq[i] = -1.

   Returns 1 if any value in iseq has been modified.   O otherwise.
 */
OSQP_API OSQPInt OSQPVectorf_ew_bounds_type(OSQPVectori*       iseq,
                                   const OSQPVectorf* l,
                                   const OSQPVectorf* u,
                                   OSQPFloat          tol,
                                   OSQPFloat          infval);


/* Elementwise replacement based on lt comparison.
   x[i] = z[i] < testval ? newval : z[i];
*/
OSQP_API void OSQPVectorf_set_scalar_if_lt(OSQPVectorf*       x,
                                  const OSQPVectorf* z,
                                  OSQPFloat          testval,
                                  OSQPFloat          newval);

/* Elementwise replacement based on gt comparison.
 * x[i] = z[i] > testval ? newval : z[i];
 */
OSQP_API void OSQPVectorf_set_scalar_if_gt(OSQPVectorf*       x,
                                  const OSQPVectorf* z,
                                  OSQPFloat          testval,
                                  OSQPFloat          newval);

# endif /* if OSQP_EMBEDDED_MODE != 1 */

#ifdef __cplusplus
}
#endif

#endif /* ifndef ALGEBRA_VECTOR_H */
