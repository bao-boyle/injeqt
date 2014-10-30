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

#include "module-impl.cpp"

#include "../mocks/mocked-provider-configuration.h"
#include "expect.h"
#include "utils.h"

#include <QtTest/QtTest>
#include <string>

using namespace injeqt::internal;
using namespace injeqt::v1;

class type_1 : public QObject
{
	Q_OBJECT

public:
	Q_INVOKABLE type_1() {}

};

class factory_type_1 : public QObject
{
	Q_OBJECT

public:
	Q_INVOKABLE type_1 * create_type_1() { return nullptr; }

};

class module_impl_test : public QObject
{
	Q_OBJECT

private slots:
	void should_properly_add_provider_configurations();

};

void module_impl_test::should_properly_add_provider_configurations()
{
	auto m = module_impl{};
	QCOMPARE(m.provider_configurations().size(), 0UL);

	auto p1 = std::unique_ptr<mocked_provider_configuration>(new mocked_provider_configuration{});
	auto p1_ptr = p1.get();
	m.add_provider_configuration(std::move(p1));
	QCOMPARE(m.provider_configurations().size(), 1UL);
	QCOMPARE(m.provider_configurations()[0].get(), p1_ptr);

	auto p2 = std::unique_ptr<mocked_provider_configuration>(new mocked_provider_configuration{});
	auto p2_ptr = p2.get();
	m.add_provider_configuration(std::move(p2));
	QCOMPARE(m.provider_configurations().size(), 2UL);
	QCOMPARE(m.provider_configurations()[0].get(), p1_ptr);
	QCOMPARE(m.provider_configurations()[1].get(), p2_ptr);

	auto p3 = std::unique_ptr<mocked_provider_configuration>(new mocked_provider_configuration{});
	auto p3_ptr = p3.get();
	m.add_provider_configuration(std::move(p3));
	QCOMPARE(m.provider_configurations().size(), 3UL);
	QCOMPARE(m.provider_configurations()[0].get(), p1_ptr);
	QCOMPARE(m.provider_configurations()[1].get(), p2_ptr);
	QCOMPARE(m.provider_configurations()[2].get(), p3_ptr);
}

QTEST_APPLESS_MAIN(module_impl_test)
#include "module-impl-test.moc"