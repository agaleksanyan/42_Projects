from pydantic import BaseModel, Field, model_validator, ValidationError
from datetime import datetime
from enum import Enum


class Rank(Enum):

    cadet = "cadet"
    officer = "officer"
    lieutenant = "lieutenant"
    captain = "captain"
    commander = "commander"


class CrewMember(BaseModel):

    member_id: str = Field(min_length=3, max_length=10)
    name: str = Field(min_length=2, max_length=50)
    rank: Rank
    age: int = Field(ge=18, le=80)
    specialization: str = Field(min_length=3, max_length=30)
    years_experience: int = Field(ge=0, le=50)
    is_active: bool = True


class SpaceMission(BaseModel):

    mission_id: str = Field(min_length=5, max_length=15)
    mission_name: str = Field(min_length=3, max_length=100)
    destination: str = Field(min_length=3, max_length=50)
    launch_date: datetime
    duration_days: int = Field(ge=1, le=3650)
    mission_status: str = "planned"
    budget_millions: float = Field(ge=1.0, le=10000.0)
    crew: list[CrewMember] = Field(min_length=1, max_length=12)

    @model_validator(mode="after")
    def validate_mission(self) -> "SpaceMission":

        if not self.mission_id.startswith("M"):
            raise ValueError("Mission ID must start with M")

        has_leader = any(
            member.rank in (Rank.commander, Rank.captain)
            for member in self.crew
        )

        if not has_leader:
            raise ValueError(
                "Mission must have at least one Commander or Captain"
            )

        if self.duration_days > 365:
            experienced_count = sum(
                1 for member in self.crew if member.years_experience >= 5
            )

            if experienced_count < len(self.crew) / 2:
                raise ValueError("Long missions need 50% experienced crew")

        all_active = all(member.is_active for member in self.crew)

        if not all_active:
            raise ValueError("All crew members must be active")

        return self


def print_mission(mission: SpaceMission) -> None:

    print("Valid mission created:")
    print(f"Mission: {mission.mission_name}")
    print(f"ID: {mission.mission_id}")
    print(f"Destination: {mission.destination}")
    print(f"Duration: {mission.duration_days} days")
    print(f"Budget: {mission.budget_millions}M")
    print(f"Crew size: {len(mission.crew)}")
    print("Crew members:")
    for member in mission.crew:
        print(
            f"- {member.name} "
            f"({member.rank.value}) - "
            f"{member.specialization}"
        )


def print_validation_errors(error: ValidationError) -> None:

    for err in error.errors():
        field = err["loc"][0] if err["loc"] else "model"
        message = err["msg"]

        print(f"Error in '{field}': {message}")


def main() -> None:

    print("Space Mission Crew Validation")
    print("=" * 40)

    try:
        crew = [
            CrewMember(
                member_id="CM001",
                name="Jhon Carter",
                rank=Rank.commander,
                age=42,
                specialization="Pilot",
                years_experience=12,
            ),
            CrewMember(
                member_id="CM002",
                name="Alice Brown",
                rank=Rank.officer,
                age=35,
                specialization="Enginner",
                years_experience=8,
            ),
            CrewMember(
                member_id="CM003",
                name="Mike Wilson",
                rank=Rank.lieutenant,
                age=30,
                specialization="Scientist",
                years_experience=6,
            ),
        ]
        mission = SpaceMission(
            mission_id="M2026_MARS",
            mission_name="Mars Exploration Mission",
            destination="Mars",
            launch_date=datetime.now(),
            duration_days=500,
            budget_millions=2500.0,
            crew=crew,
        )

        print_mission(mission)

    except ValidationError as e:

        print_validation_errors(e)

    print("=" * 40)

    try:

        bad_crew = [
            CrewMember(
                member_id="CM010",
                name="Tom",
                rank=Rank.officer,
                age=28,
                specialization="Engineer",
                years_experience=2,
            ),
            CrewMember(
                member_id="CM011",
                name="Sam",
                rank=Rank.lieutenant,
                age=25,
                specialization="Scientist",
                years_experience=1,
            ),
        ]

        SpaceMission(
            mission_id="M2026_BAD",
            mission_name="Failed Mission",
            destination="Moon",
            launch_date=datetime.now(),
            duration_days=100,
            budget_millions=500.0,
            crew=bad_crew,
        )

    except ValidationError as e:

        print("Expected validation error:")
        print_validation_errors(e)


if __name__ == "__main__":
    main()
