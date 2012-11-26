/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2012 Kyle McQuisten
 * Copyright (C) 2012 Kyle McQuisten
 */

#ifndef _EDITSTRINGKERNEL_H___
#define _EDITSTRINGKERNEL_H___

#include <shogun/lib/common.h>
#include <shogun/kernel/string/StringKernel.h>
#include <shogun/features/StringFeatures.h>

namespace shogun
{
/** @brief The Edit String Kernel computed on CStringFeatures<char>.
 *
 * It is computed as
 *
 * \f[
 * k({\bf x},{\bf x'})= exp{-\gamma \cdot edit(x,x')}
 * \f]
 *
 * where $\gamma$ is the width parameter and $e(x,x')$ is the Levenshtein (edit) distance between strings $x$ and $x'$.
 *
 */
class CEditStringKernel: public CStringKernel<char>
{
	public:
		/** default constructor
		 *
		 */
		CEditStringKernel();

		/** constructor
		 *
		 * @param size cache size
		 * @param width width
		 */
		CEditStringKernel(float64_t gamma);

		/** constructor
		 *
		 * @param l features of left-hand side
		 * @param r features of right-hand side
		 * @param gamma gamma
		 */
		CEditStringKernel(CDotFeatures* l, CDotFeatures* r,	float64_t gamma);

		virtual ~CEditStringKernel();

		/** initialize kernel
		 *
		 * @param l features of left-hand side
		 * @param r features of right-hand side
		 * @return if initializing was successful
		 */
		virtual bool init(CFeatures* l, CFeatures* r);

		/** clean up kernel */
		virtual void cleanup();

		/** return what type of kernel we are
		 *
		 * @return kernel type EDIT
		 */
		virtual EKernelType get_kernel_type() { return K_EDIT; }

		/** return the kernel's name
		 *
		 * @return name EditString
		 */
		virtual const char* get_name() const { return "EditStringKernel"; }

		/** set the kernel's gamma
		 *
		 * @param w kernel gamma
		 */
		virtual void set_gamma(float64_t g)
		{
			gamma=g;
		}

		/** return the kernel's gamma
		 *
		 * @return kernel gamma
		 */
		virtual float64_t get_gamma() const
		{
			return gamma;
		}

		/** return derivative with respect to specified parameter
		 *
		 * @param param the parameter
		 * @param obj the object that owns the parameter
		 * @param index the index of the element if parameter is a vector
		 *
		 * @return gradient with respect to parameter
		 */
		virtual SGMatrix<float64_t> get_parameter_gradient(TParameter* param,
				CSGObject* obj, index_t index = -1);


	protected:
		/** helper for compute that calculates the edit distance
		 *
		 * @param idx_a index a
		 * @param idx_b index b
		 * @return computed value
		 */
		virtual float64_t compute_helper(int32_t idx_a, int32_t idx_b);

		/** compute kernel function for features a and b
		 * idx_{a,b} denote the index of the feature vectors
		 * in the corresponding feature object
		 *
		 * @param idx_a index a
		 * @param idx_b index b
		 * @return computed kernel function at indices a,b
		 */
		virtual float64_t compute(int32_t idx_a, int32_t idx_b);

	private:
		void init();

	protected:
		/** gamma */
		float64_t gamma;

};
}
#endif /* _EDITSTRINGKERNEL_H__ */
