/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2012 Chiyuan Zhang
 * Copyright (C) 2012 Chiyuan Zhang
 */

#include <shogun/multiclass/tree/RelaxedTree.h>

using namespace shogun;

CRelaxedTree::CRelaxedTree()
	:m_feats(NULL)
{
}

CRelaxedTree::~CRelaxedTree()
{
	SG_UNREF(m_feats);
}

CMulticlassLabels* CRelaxedTree::apply_multiclass(CFeatures* data)
{
	if (data)
	{
		CDenseFeatures<float64_t> feats = dynamic_cast<CDenseFeatures<float64_t>*>(data);
		if (feats == NULL)
			SG_ERROR("Require non-NULL dense features of float64_t\n");
		set_features(feats);
	}
	return NULL;
}

bool CRelaxedTree::train_machine(CFeatures* data)
{
	return false;
}
