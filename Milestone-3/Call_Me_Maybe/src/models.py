from pydantic import BaseModel

class TypeDefinition(BaseModel):
    type: str
    
class FunctionCallingTest(BaseModel):
    prompt: str
    
class FunctionDefinition(BaseModel):
    name: str
    description: str
    parameters: dict[str, TypeDefinition]
    returns: TypeDefinition