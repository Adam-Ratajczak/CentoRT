# CentoRT buildsystem proposal

## 1. Buildsystem

CentoRT goal is to unify many technologies in one simple .yaml based buildsystem. User shouldn't need to spend hours to patch up many different programming technologies, compilers and interfaces in order to make a multilanguage project. .yaml manifest should handle all the necessary fetching dependencies, building and linkage for them.

### 1.1. Common attributes

Below, there are attributes that may be used in any of the YAML objects specified further

#### 1.1.1.1. vars: `<dict>`

User specifies variables dictionary (key : value) that may be later used to substitute `${VAR_NAME}` syntax. In case of endless loop in `vars` dictionary, buildsystem shall throw an error. Using variables in keys ov `vars` dictionary is forbidden.