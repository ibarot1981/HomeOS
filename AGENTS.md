# AGENTS.md

# HomeOS – AI Agent Instructions

This file contains the permanent engineering instructions for any AI agent working on the HomeOS repository.

These instructions define how work should be planned, implemented, tested, documented, committed, and delivered.

If any instruction in this file conflicts with an explicit instruction from the user in the current task, the user's instruction takes precedence unless it would risk data loss, unsafe hardware behavior, credential exposure, or repository corruption.

---

# 1. Project Objective

HomeOS is a long-term ESP32-S3 based home automation and monitoring platform.

The project should grow slowly, safely, and maintainably.

Primary goals:

- Reliability
- Maintainability
- Simplicity
- Clear documentation
- Incremental growth
- Educational value
- Safe hardware practices

Do not optimize for writing the largest amount of code.

Always optimize for writing the smallest amount of correct, understandable, maintainable code.

---

# 2. Source of Truth

The repository documentation is the authoritative specification for this project.

Before beginning work, read the documents relevant to the task.

At minimum, always read:

- `docs/Development-Workflow.md`

Depending on the task, also read:

- `docs/Architecture.md`
- `docs/Coding-Standards.md`
- `docs/Hardware.md`
- `docs/Wiring.md`
- `docs/ESP32.md`
- `docs/Display.md`
- `docs/Modules.md`
- `docs/Roadmap.md`
- `docs/Decisions.md`
- `docs/Testing.md`
- `docs/UI.md`

Never invent architecture, wiring, workflows, or implementation details that contradict the documentation.

When documentation and implementation disagree, stop and report the inconsistency.

---

# 3. Development Philosophy

Follow these principles:

- Keep solutions simple.
- Avoid premature optimization.
- Avoid unnecessary abstractions.
- Implement only what is required for the current milestone or task.
- Design so future growth remains possible.
- Prefer readability over cleverness.
- Prefer explicit code over magic.
- Prefer maintainability over brevity.
- Prefer boring, reliable solutions over impressive but fragile solutions.

This is a long-term project. Code should be easy to understand months later.

---

# 4. Incremental Architecture Rule

The architecture must grow incrementally.

Do not introduce the following unless they are required by the current roadmap milestone or explicitly approved by the user:

- Event bus
- Scheduler framework
- Service locator
- Dependency injection framework
- Plugin system
- Generic module framework
- Generic configuration framework
- Complex state machines
- Large-scale refactoring

Never build infrastructure only because it may be useful later.

For early versions, prefer direct, simple, readable implementation.

---

# 5. Monitoring Before Control

HomeOS should initially focus on monitoring, display, logging, and safe feedback.

Do not add control of electrical loads, relays, appliances, mains-powered devices, or safety-critical systems unless the user explicitly approves the scope and the hardware safety design is documented.

When in doubt, choose observation over control.

---

# 6. Documentation Is Part of the Product

A task is not complete until the documentation matches the implementation.

Whenever code, wiring, hardware, architecture, dependencies, setup steps, tests, or workflows change, update the relevant documentation.

Common examples:

- Firmware behavior changed → update relevant module or architecture docs.
- Wiring changed → update `docs/Wiring.md`.
- Hardware changed → update `docs/Hardware.md`.
- ESP32 board assumptions changed → update `docs/ESP32.md`.
- Display assumptions changed → update `docs/Display.md`.
- Workflow changed → update `docs/Development-Workflow.md`.
- Design decision made → update `docs/Decisions.md`.
- Milestone status changed → update `docs/Roadmap.md`.
- User-visible change made → update `CHANGELOG.md` where appropriate.

Never leave documentation knowingly outdated.

---

# 7. Before Writing Code

Before implementing:

1. Understand the user request.
2. Check the current Git branch and working tree.
3. Read the relevant documentation.
4. Inspect the existing implementation.
5. Identify the smallest safe change.
6. Avoid unrelated edits.
7. Avoid rewriting working code unless necessary.

Do not begin large changes without understanding the existing structure.

---

# 8. Code Quality Rules

Code should be:

- Readable
- Modular
- Consistently formatted
- Easy to debug
- Free of dead code
- Free of unused variables
- Free of unnecessary dependencies
- Commented where the reason is not obvious

Avoid duplication, but do not create premature abstractions just to remove two similar lines of code.

Use descriptive names.

Prefer clear control flow.

Avoid clever shortcuts.

---

# 9. Git Workflow

Do not work directly on `main` for implementation tasks.

Default workflow:

1. Confirm the working tree is clean.
2. Pull the latest changes from `origin/main`.
3. Create a feature branch from `main`.
4. Make the required changes.
5. Run relevant validation and tests.
6. Review the full diff.
7. Confirm no secrets, generated build artifacts, or unrelated files are included.
8. Commit with a clear descriptive message.
9. Push the branch to `origin`.
10. Create a pull request against `main`.
11. Stop and wait for user approval before merging.

Never merge automatically.

Never force-push unless explicitly instructed.

Never rewrite published history unless explicitly instructed.

Never commit directly to `main` unless the user explicitly asks for a direct commit and the change is low-risk.

---

# 10. Branch Naming

Use clear branch names.

Preferred patterns:

- `feature/<short-description>`
- `fix/<short-description>`
- `docs/<short-description>`
- `chore/<short-description>`
- `test/<short-description>`

Examples:

- `feature/display-vendor-example`
- `fix/esp32-board-detection`
- `docs/add-agents-instructions`
- `chore/create-platformio-skeleton`

---

# 11. Commit Rules

Commits should be small, logical, and reviewable.

A commit message should clearly describe what changed.

Good examples:

- `Add initial PlatformIO firmware skeleton`
- `Document ESP32-S3 board verification steps`
- `Fix display pin mapping notes`
- `Add AGENTS.md workflow instructions`

Avoid vague messages such as:

- `updates`
- `changes`
- `fix`
- `misc`

Do not include unrelated changes in the same commit.

---

# 12. Pull Request Rules

Every implementation branch should result in a pull request unless the user explicitly asks otherwise.

If an agent asks the user to create the pull request, the agent must provide the pull request title and a ready-to-paste description body. Do not only provide the branch name or GitHub "create pull request" link.

The pull request summary should include:

- What changed
- Why it changed
- Files changed
- Documentation updated
- Tests or validation performed
- Known limitations
- Anything requiring user review

When the agent cannot create the pull request directly because of tool or permission limitations, the final response should include:

- the branch name
- the pull request target branch
- the pull request title
- the ready-to-paste pull request description
- the GitHub pull request creation link, if available

Do not merge the pull request without explicit user approval.

---

# 13. Safety Rules

Never commit:

- Passwords
- API keys
- Tokens
- Private keys
- Certificates
- Wi-Fi credentials
- Personal access tokens
- `.env` files containing secrets

Never expose secrets in logs, documentation, commits, examples, screenshots, or comments.

Never delete user data without explicit instruction.

Never modify unrelated files.

Never make destructive Git operations unless explicitly instructed.

---

# 14. Hardware Safety Rules

Safety has priority over convenience.

Never assume:

- Voltage
- Current capacity
- GPIO tolerance
- Pinout
- Polarity
- Connector function
- Power supply capability
- Sensor module behavior

Verify using documentation, datasheets, measurements, or explicit user confirmation.

If uncertain, stop and ask.

Never recommend connecting ESP32 GPIO directly to Indian 230V mains electricity.

Never suggest unsafe mains wiring.

Any future mains-related control must use properly rated isolation, certified modules, enclosures, fuses, and safe electrical practices.

For uncertain hardware, document assumptions clearly before implementation.

---

# 15. ESP32 Rules

This project targets ESP32-S3, but the exact board revision and exposed USB behavior must be verified.

Do not assume:

- Native USB is exposed
- PSRAM is available
- Flash size is known
- Pin labels match GPIO numbers
- Boot and reset behavior is identical across boards

When firmware depends on board capabilities, verify and document the result.

Prefer simple serial diagnostics during early development.

---

# 16. Display Rules

The ePaper display must be treated as hardware that requires validation.

Do not assume:

- Partial refresh works
- Fast refresh works
- The controller exactly matches the listing
- The GxEPD2 driver is correct
- The pinout is confirmed

Version 0.1 should first prove the vendor example or a minimal known-good display test before building higher-level UI features.

Document the confirmed display model, controller, driver, wiring, and test result.

---

# 17. Testing and Validation

Before considering work complete:

- Build successfully.
- Run applicable tests.
- Run relevant firmware validation where possible.
- Confirm no new warnings are introduced.
- Confirm documentation is updated.
- Confirm the Git diff is clean and intentional.

If testing cannot be performed, clearly state:

- What was not tested
- Why it was not tested
- What the user should test manually

Do not claim tests passed unless they actually ran.

---

# 18. Architecture Changes

Do not make architecture changes silently.

If a task appears to require:

- Restructuring
- Major refactoring
- New framework
- New dependency
- Public interface change
- New architectural pattern
- Change to the roadmap direction

Then explain:

- What change is proposed
- Why it is needed
- Benefits
- Drawbacks
- Safer alternatives

Wait for user approval before proceeding.

---

# 19. Dependency Rules

Avoid adding dependencies unless necessary.

Before adding a dependency, consider:

- Is it required now?
- Is it maintained?
- Is it compatible with ESP32-S3?
- Does it increase firmware size significantly?
- Can the same result be achieved simply without it?

Document any important dependency additions.

---

# 20. Generated Files and Build Artifacts

Do not commit generated build outputs unless explicitly required.

Common files and folders that should usually not be committed:

- `.pio/`
- build folders
- temporary logs
- cache files
- local environment files
- editor-specific clutter
- generated binaries unless explicitly requested

Keep `.gitignore` updated as the project evolves.

---

# 21. Teaching and Explanation

The user is using this project partly to learn ESP32, Git, and good development workflow.

When completing work, provide concise explanations of important concepts involved.

Explain enough to help the user understand what changed and why.

Do not write long tutorials unless asked.

Prefer practical engineering explanations.

---

# 22. Communication Style

When completing a task, provide:

- Summary
- Branch name
- Commit message
- Files changed
- Documentation updated
- Tests run
- Pull request link or status
- Remaining work or known limitations

Be concise and specific.

Do not hide uncertainty.

Do not claim completion if a step failed.

---

# 23. Definition of Done

A task is complete only when:

- Code or documentation changes are implemented.
- Relevant documentation is updated.
- `CHANGELOG.md` is updated when appropriate.
- Build passes where applicable.
- Tests or validation checks are run where applicable.
- Diff is reviewed.
- No secrets or unrelated files are included.
- A clean commit is created.
- The branch is pushed.
- A pull request is created when appropriate.
- The user is informed of results and any limitations.

If any of these are not done, clearly state what remains.

---

# 24. Final Principle

Leave the repository in a better state than you found it.

Small, safe improvements are encouraged.

Large unsolicited redesigns are not.
