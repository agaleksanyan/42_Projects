from pydantic import BaseModel, Field, model_validator, ValidationError
from datetime import datetime
from enum import Enum


class ContactType(Enum):

    radio = "radio"
    visual = "visual"
    physical = "physical"
    telepathic = "telepathic"


class AlienContact(BaseModel):

    contact_id: str = Field(min_length=5, max_length=15)

    timestamp: datetime

    location: str = Field(min_length=3, max_length=100)

    contact_type: ContactType

    signal_strength: float = Field(ge=0.00, le=10.00)

    duration_minutes: int = Field(ge=1, le=1440)

    witness_count: int = Field(ge=1, le=100)

    message_received: str | None = Field(default=None, max_length=500)

    is_verified: bool = False

    @model_validator(mode="after")
    def validate_contact(self) -> "AlienContact":

        if not self.contact_id.startswith("AC"):
            raise ValueError("contact ID must start with AC")

        if self.contact_type == ContactType.physical and not self.is_verified:
            raise ValueError("Physical contact reports must be verified")

        if (
            self.contact_type == ContactType.telepathic
            and self.witness_count < 3
        ):
            raise ValueError(
                "Telepathic contact requires at least 3 witnesses"
                )

        if self.signal_strength > 7.0 and not self.message_received:
            raise ValueError("Strong signals should include received message")

        return self


def print_contact(contact: AlienContact) -> None:

    print("Valid contact report:")

    print(f"ID: {contact.contact_id}")
    print(f"Type: {contact.contact_type.value}")
    print(f"Location: {contact.location}")
    print(f"Signal: {contact.signal_strength}/10")
    print(f"Duration: " f"{contact.duration_minutes} minutes")
    print(f"Witnesses: " f"{contact.witness_count}")

    if contact.message_received:
        print(f"Message: " f"'{contact.message_received}'")

    print(f"Verified: " f"{contact.is_verified}")


def print_validation_errors(error: ValidationError) -> None:

    for err in error.errors():
        field = err["loc"][0] if err["loc"] else "model"
        message = err["msg"]

        print(f"Error in '{field}': {message}")


def main() -> None:

    print("Alien Contact Log Validation")
    print("=" * 40)

    try:

        contact = AlienContact(
            contact_id="AC_2024_001",
            timestamp=datetime.now(),
            location="Area 51, Nevada",
            contact_type=ContactType.radio,
            signal_strength=8.5,
            duration_minutes=45,
            witness_count=5,
            message_received="Greetings from Zeta Reticuli",
        )

        print_contact(contact)

    except ValidationError as e:

        print("Expected validation error:")
        print_validation_errors(e)

    print("=" * 40)

    try:

        invalid = AlienContact(
            contact_id="AC_002",
            timestamp=datetime.now(),
            location="Mars",
            contact_type=ContactType.telepathic,
            signal_strength=5.0,
            duration_minutes=20,
            witness_count=1,
        )

        print_contact(invalid)

    except ValidationError as e:

        print("Expected validation error:")
        print_validation_errors(e)


if __name__ == "__main__":
    main()
