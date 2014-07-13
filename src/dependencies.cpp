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

#include "dependencies.h"

#include "dependency.h"

namespace injeqt { namespace v1 {

bool dependencies::less_than_dependency(const dependency &left, const dependency &right)
{
	return std::addressof(left.type()) < std::addressof(right.type());
}

bool dependencies::equal_dependency(const dependency &left, const dependency &right)
{
	return std::addressof(left.type()) == std::addressof(right.type());
}

dependencies::dependencies(std::vector<dependency> dependencies) :
	_content{std::move(dependencies)}
{
}

dependencies::storage_type::const_iterator dependencies::begin() const
{
	return _content.begin();
}

dependencies::storage_type::const_iterator dependencies::end() const
{
	return _content.end();
}

bool dependencies::empty() const
{
	return _content.empty();
}

typename dependencies::storage_type::size_type dependencies::size() const
{
	return _content.size();
}

}}
