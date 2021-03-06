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

#include "expect.h"
#include "utils.h"

#include "internal/default-constructor-method.h"

#include <QtTest/QtTest>
#include <string>

using namespace injeqt::internal;
using namespace injeqt::v1;

class no_default_constructor : public QObject
{
	Q_OBJECT

public:
	Q_INVOKABLE no_default_constructor(int a) { (void)a; }
	Q_INVOKABLE no_default_constructor(std::string a) { (void)a; }

};

class default_not_invokable_constructor : public QObject
{
	Q_OBJECT

public:
	default_not_invokable_constructor() {}

};

class default_invokable_constructor : public QObject
{
	Q_OBJECT

public:
	Q_INVOKABLE default_invokable_constructor(QObject *parent = nullptr) : QObject{parent} {}

};

class default_invokable_constructor_no_parameters : public QObject
{
	Q_OBJECT

public:
	Q_INVOKABLE default_invokable_constructor_no_parameters() {}

};

class default_constructor_method_test : public QObject
{
	Q_OBJECT

private slots:
	void should_return_empty_when_default_constructed();
	void should_return_empty_when_created_with_not_default_constructor();
	void should_return_empty_when_created_with_not_invokable_constructor();
	void should_create_valid_with_invokable_constructor();
	void should_create_object_with_default_constructor();
	void should_properly_compare();

};

void default_constructor_method_test::should_return_empty_when_default_constructed()
{
	auto c = default_constructor_method{};
	QVERIFY(c.is_empty());
}

void default_constructor_method_test::should_return_empty_when_created_with_not_default_constructor()
{
	auto c = make_default_constructor_method(make_type<no_default_constructor>());
	QVERIFY(c.is_empty());
}

void default_constructor_method_test::should_return_empty_when_created_with_not_invokable_constructor()
{
	auto c = make_default_constructor_method(make_type<default_not_invokable_constructor>());
	QVERIFY(c.is_empty());
}

void default_constructor_method_test::should_create_valid_with_invokable_constructor()
{
	auto c = make_default_constructor_method(make_type<default_invokable_constructor>());
	QVERIFY(!c.is_empty());
	QCOMPARE(c.object_type(), make_type<default_invokable_constructor>());
}

void default_constructor_method_test::should_create_object_with_default_constructor()
{
	auto c = make_default_constructor_method(make_type<default_invokable_constructor>());
	QVERIFY(!c.is_empty());

	auto object = c.invoke();
	auto cast = qobject_cast<default_invokable_constructor *>(object.get());
	QVERIFY(cast != nullptr);
}

void default_constructor_method_test::should_properly_compare()
{
	auto c_empty = default_constructor_method{};
	auto c1a = make_default_constructor_method(make_type<default_invokable_constructor>());
	auto c1b = make_default_constructor_method(make_type<default_invokable_constructor>());
	auto c2a = make_default_constructor_method(make_type<default_invokable_constructor_no_parameters>());
	auto c2b = make_default_constructor_method(make_type<default_invokable_constructor_no_parameters>());
	
	test_compare<default_constructor_method>({{c_empty}, {c1a, c1b}, {c2a, c2b}});
}

QTEST_APPLESS_MAIN(default_constructor_method_test)
#include "default-constructor-method-test.moc"
