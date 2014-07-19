/*
 * %injeqt copyright begin%
 * Copyright 2014 Rafał Malinowski (rafal.przemyslaw.malinowski@gmail.com)
 * %injeqt copyright end%
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "setter-method.h"

namespace injeqt { namespace v1 {

setter_method::setter_method(type object_type, type parameter_type, QMetaMethod meta_method) :
	_object_type{std::move(object_type)},
	_parameter_type{std::move(parameter_type)},
	_meta_method{std::move(meta_method)}
{
}

type setter_method::object_type() const
{
	return _object_type;
}

type setter_method::parameter_type() const
{
	return _parameter_type;
}

QMetaMethod setter_method::meta_method() const
{
	return _meta_method;
}

bool operator == (const setter_method &x, const setter_method &y)
{
	if (std::addressof(x) == std::addressof(y))
		return true;

	if (x.object_type() != y.object_type())
		return false;

	if (x.parameter_type() != y.parameter_type())
		return false;

	if (x.meta_method() != y.meta_method())
		return false;

	return true;
}

bool operator != (const setter_method &x, const setter_method &y)
{
	return !(x == y);
}

}}
