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

#include "dependency.cpp"
#include "dependency-apply-method.h"
#include "dependency-resolver.cpp"
#include "implements-extractor.cpp"
#include "injeqt-object.cpp"
#include "meta-object.cpp"
#include "meta-object-factory.cpp"
#include "resolved-dependency.cpp"

#include <QtCore/QMetaObject>
#include <QtTest/QtTest>

using namespace injeqt::v1;

class injectable_type1 : public QObject
{
	Q_OBJECT
};

class injectable_type2 : public QObject
{
	Q_OBJECT
};

class injectable_type3 : public QObject
{
	Q_OBJECT
};

class dependency_resolver_test : public QObject
{
	Q_OBJECT

private slots:
	void should_properly_resolve_simple_dependency();

private:
	template<typename T>
	injeqt_object make_injeqt_object();

};

template<typename T>
injeqt_object dependency_resolver_test::make_injeqt_object()
{
	auto qobject = std::unique_ptr<QObject>(new T{});
	auto object = injeqt_object
	{
		meta_object_factory{}.create_meta_object(T::staticMetaObject),
		std::move(qobject)
	};

	return object;
}

void dependency_resolver_test::should_properly_resolve_simple_dependency()
{
	auto object1 = make_injeqt_object<injectable_type1>();
	auto object2 = make_injeqt_object<injectable_type2>();
	auto object3 = make_injeqt_object<injectable_type3>();
	auto objects = std::vector<const injeqt_object *>{
		std::addressof(object1),
		std::addressof(object2),
		std::addressof(object3)
	};
	auto to_resolve = dependency{
		injectable_type1::staticMetaObject,
		dependency_apply_method::setter,
		QMetaMethod{}
	};

	auto resolved = dependency_resolver{}.resolve_dependency(to_resolve, objects);
	QCOMPARE(resolved, std::addressof(object1));
}

QTEST_APPLESS_MAIN(dependency_resolver_test);

#include "dependency-resolver-test.moc"