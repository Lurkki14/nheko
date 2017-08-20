/*
 * nheko Copyright (C) 2017  Konstantinos Sideris <siderisk@auth.gr>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <QJsonValue>
#include <QMap>

#include "Deserializable.h"

namespace matrix
{
namespace events
{
enum class PowerLevels {
	User = 0,
	Moderator = 50,
	Admin = 100,
};

/*
 * Defines the power levels (privileges) of users in the room.
 */

class PowerLevelsEventContent
  : public Deserializable
  , public Serializable
{
public:
	void deserialize(const QJsonValue &data) override;
	QJsonObject serialize() const override;

	inline int banLevel() const;
	inline int inviteLevel() const;
	inline int kickLevel() const;
	inline int redactLevel() const;

	inline int eventsDefaultLevel() const;
	inline int stateDefaultLevel() const;
	inline int usersDefaultLevel() const;

	int eventLevel(QString event_type) const;
	int userLevel(QString user_id) const;

private:
	int ban_ = static_cast<int>(PowerLevels::Moderator);
	int invite_ = static_cast<int>(PowerLevels::Moderator);
	int kick_ = static_cast<int>(PowerLevels::Moderator);
	int redact_ = static_cast<int>(PowerLevels::Moderator);

	int events_default_ = static_cast<int>(PowerLevels::User);
	int state_default_ = static_cast<int>(PowerLevels::Moderator);
	int users_default_ = static_cast<int>(PowerLevels::User);

	QMap<QString, int> events_;
	QMap<QString, int> users_;
};

inline int
PowerLevelsEventContent::banLevel() const
{
	return ban_;
}

inline int
PowerLevelsEventContent::inviteLevel() const
{
	return invite_;
}

inline int
PowerLevelsEventContent::kickLevel() const
{
	return kick_;
}

inline int
PowerLevelsEventContent::redactLevel() const
{
	return redact_;
}

inline int
PowerLevelsEventContent::eventsDefaultLevel() const
{
	return events_default_;
}

inline int
PowerLevelsEventContent::stateDefaultLevel() const
{
	return state_default_;
}

inline int
PowerLevelsEventContent::usersDefaultLevel() const
{
	return users_default_;
}
} // namespace events
} // namespace matrix
