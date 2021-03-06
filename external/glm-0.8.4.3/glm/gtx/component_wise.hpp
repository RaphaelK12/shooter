///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2009 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-05-21
// Updated : 2007-05-21
// Licence : This source is under MIT License
// File    : glm/gtx/component_wise.h
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_component_wise
#define glm_gtx_component_wise

// Dependency:
#include "../glm.hpp"

namespace glm
{
	namespace test{
		void main_gtx_component_wise();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_component_wise extension: Operations between components of a type
	namespace component_wise
	{
		//! Add all vector components together. 
		//! From GLM_GTX_component_wise extension.
		template <typename genType> 
		typename genType::value_type compAdd(
			genType const & v);

		//! Multiply all vector components together. 
		//! From GLM_GTX_component_wise extension.
		template <typename genType> 
		typename genType::value_type compMul(
			genType const & v);

		//! Find the minimum value between single vector components.
		//! From GLM_GTX_component_wise extension.
		template <typename genType> 
		typename genType::value_type compMin(
			genType const & v);

		//! Find the maximum value between single vector components.
		//! From GLM_GTX_component_wise extension.
		template <typename genType> 
		typename genType::value_type compMax(
			genType const & v);

	}//namespace component_wise
	}//namespace gtx
}//namespace glm

#define GLM_GTX_component_wise namespace gtx::component_wise
#ifndef GLM_GTX_GLOBAL
namespace glm {using GLM_GTX_component_wise;}
#endif//GLM_GTC_GLOBAL

#include "component_wise.inl"

#endif//glm_gtx_component_wise
