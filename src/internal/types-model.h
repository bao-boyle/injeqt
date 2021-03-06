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

#pragma once

#include <injeqt/injeqt.h>
#include <injeqt/type.h>

#include "implemented-by-mapping.h"
#include "internal.h"
#include "types-by-name.h"
#include "types-dependencies.h"

/**
 * @file
 * @brief Contains classes and functions for representing model of Injeqt types.
 */

namespace injeqt { namespace internal {

/**
 * @brief Model of all types, their dependencies and relations.
 *
 * This class is used to represent model of all types, their dependencies and relations.
 * Basically it consists of implemented_by_mapping and types_dependencies build from
 * the same set of types.
 *
 * Use make_types_model(const std::vector<type> &) to create valid instance of this type
 * and be informed of any errors in form of exceptions.
 */
class INJEQT_INTERNAL_API types_model
{

public:
	/**
	 * @brief Create empty instance of types_model.
	 */
	types_model();

	/**
	 * @brief Create new instance of types_model.
	 * @param available_types set of all interfaces in model mapped to implementation types
	 * @param mapped_dependencies set of all dependencies of implementation types
	 *
	 * Both @p available_types and @p mapped_dependencies should be created from the same set of
	 * types for types_model to be usefull.
	 */
	explicit types_model(implemented_by_mapping available_types, types_dependencies mapped_dependencies);

	/**
	 * @return set of all interfaces in model mapped to implementation types.
	 */
	const implemented_by_mapping & available_types() const;

	/**
	 * @return set of all dependencies of implementation types
	 */
	const types_dependencies & mapped_dependencies() const;

	/**
	 * @return true if model contains @p interface_type
	 */
	bool contains(const type &interface_type) const;

	/**
	 * @brief Return all unresolvable dependencies
	 */
	std::vector<dependency> get_unresolvable_dependencies() const;

private:
	implemented_by_mapping _available_types;
	types_dependencies _mapped_dependencies;

};

/**
 * @brief Create types_model from given set of types.
 * @param known_types list of all known types
 * @param all_types set of types to make model from, all types must be valid.
 * @param need_dependencies list of types that will have dependencies extracted
 * @post result.get_unresolvable_dependencies().empty()
 * @throw ambiguous_types if one or more types is ambiguous (@see make_type_relations)
 * @throw unresolvable_dependencies if a type has a dependency type not in @p all_types set
 * @throw dependency_on_self when type depends on self
 * @throw dependency_on_subtype when type depends on own supertype
 * @throw dependency_on_subtype when type depends on own subtype
 * @throw invalid_setter if any tagged setter has parameter that is not a QObject-derived pointer
 * @throw invalid_setter if any tagged setter has parameter that is a QObject pointer
 * @throw invalid_setter if any tagged setter has other number of parameters than one
 */
INJEQT_INTERNAL_API types_model make_types_model(const types_by_name &known_types, const std::vector<type> &all_types, const std::vector<type> &need_dependencies);

/**
 * @brief Check if types model do not have unresolvable types.
 * @param model model to check
 * @throw unresolvable_dependencies if @p model contains unresolvable types
 */
INJEQT_INTERNAL_API void validate_non_unresolvable(const types_model &model);

}}
