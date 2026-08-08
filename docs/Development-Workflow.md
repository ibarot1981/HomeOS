# Development Workflow

**This document defines how HomeOS is developed. Every implementation task must follow these rules. Documentation is considered part of the product.**

## Purpose

This document defines the engineering workflow for the HomeOS project.

HomeOS is expected to grow over months, with firmware, hardware, wiring, documentation, and testing all evolving together. This workflow keeps those parts aligned so the project remains understandable, buildable, and safe to extend.

The goal is simple: every milestone should leave behind working code, accurate documentation, and a clear record of what changed.

## Golden Rule

**A feature is NOT complete until both the code AND all affected documentation have been updated.**

Documentation is part of the product. If the firmware changes but the documentation still describes the old behavior, the project is not finished.

## Living Documentation

Every Markdown document in HomeOS is a living document.

Documentation must represent the current implementation, current hardware assumptions, and current project decisions. Outdated documentation is considered a project defect because it can lead to wrong wiring, wrong expectations, unsafe assumptions, or wasted debugging time.

When code and documentation disagree, the disagreement itself must be treated as something to fix.

## Documentation Update Matrix

| If you change... | You must update... |
|------------------|--------------------|
| Hardware | `Hardware.md` |
| Wiring | `Wiring.md` |
| Display | `Display.md` |
| ESP32 configuration | `ESP32.md` |
| Architecture | `Architecture.md` |
| Modules | `Modules.md` |
| UI | `UI.md` |
| Roadmap | `Roadmap.md` |
| Electronics explanations | `Electronics-Basics.md` |
| Major engineering decisions | `Decisions.md` |
| Build or deployment | `Deployment.md` |
| Testing procedure | `Testing.md` |
| Project overview | `README.md` |
| Project scope | `Project.md` |
| Milestone completion | `CHANGELOG.md` |
| Material system structure or code-flow change | `Architecture.md`, `Code-Map.md`, and `visualizations/homeos-code-map.html` |

## Definition of Done

A task is considered complete only when:

- code compiles successfully
- existing functionality is not broken
- relevant documentation has been updated
- architecture, static code map, and interactive code map have been reviewed and updated when system structure or code flow changed
- `CHANGELOG.md` has been updated if the change is user-visible or milestone-worthy
- tests have been updated where appropriate
- new files are documented
- known limitations are documented
- version or milestone references are updated if applicable

For hardware tasks, "done" also means the wiring assumptions and safety notes have been checked against the actual component, not only against a product title or seller listing.

## Documentation Debt

If implementation is complete but documentation is not updated, the task status is **Documentation Debt**, not **Completed**.

Documentation debt should be resolved before starting the next milestone. Small notes are acceptable during active experimentation, but the repository should not drift into a state where only the person who last touched it understands what is true.

## Milestone Philosophy

Every milestone should leave the repository in a working state.

Avoid half-finished frameworks, partially implemented systems, or large scaffolds that do not run. A small working milestone is better than a large architecture that only exists on paper.

Examples:

- Version 0.1 should prove the board, serial logging, and display test screen.
- Version 0.3 should prove actual button navigation, not only create empty button classes.
- Version 0.5 should prove display modes with real module behavior.

## Incremental Development

HomeOS has a target architecture, but it should be implemented incrementally.

Rules:

- build only what is needed for the current milestone
- avoid premature abstractions
- refactor intentionally when milestones require it
- prefer one working vertical slice over many unused layers
- keep the architecture direction stable while letting implementation grow step by step

This matters especially in firmware because debugging can involve both code and physical wiring. Smaller changes are easier to test and easier to explain.

## Repository Discipline

Keep the repository clean.

Rules:

- no dead code
- no unused libraries
- no placeholder classes that are never used
- avoid TODO accumulation
- remove experimental code after decisions are made
- do not commit secrets such as WiFi passwords, Telegram bot tokens, or API keys
- keep examples separate from production firmware

Temporary experiments are allowed during learning, but they should either become documented project code or be removed.

## Local GitHub SSH Setup

This Windows PC uses the SSH host alias `github-newspaper-bot` for GitHub access to the HomeOS repository.

The correct HomeOS remote URL is:

```text
git@github-newspaper-bot:ibarot1981/HomeOS.git
```

Do not replace this remote with HTTPS. Do not replace it with `git@github.com:ibarot1981/HomeOS.git` unless the SSH configuration is changed to support the plain `github.com` host directly.

The SSH configuration file is:

```text
%USERPROFILE%\.ssh\config
```

It should contain an entry shaped like this:

```ssh
Host github-newspaper-bot
    HostName github.com
    User git
    IdentityFile ~/.ssh/<github-private-key-file>
    IdentitiesOnly yes
```

The correct SSH test command is:

```powershell
ssh -T git@github-newspaper-bot
```

A successful result looks like:

```text
Hi ibarot1981! You've successfully authenticated, but GitHub does not provide shell access.
```

Plain `ssh -T git@github.com` is expected to fail on this PC unless a separate `github.com` SSH configuration is added.

## Hardware Documentation Rules

Every newly purchased hardware component should eventually have documented:

- product link
- seller
- photos
- wiring
- pinout
- known issues
- compatibility notes

For electronics, exact identification matters. A product title is not enough. Two parts with similar names can have different pinouts, voltage requirements, controller chips, or library support.

If a component has not been fully identified yet, mark the relevant fields as `TBD` rather than guessing.

## Codex Responsibilities

Whenever implementing a task, Codex should:

1. Review affected documentation.
2. Implement the code.
3. Update all affected Markdown files, including `Architecture.md`, `Code-Map.md`, and `visualizations/homeos-code-map.html` when the implementation materially changes system structure or code flow.

For normal firmware evolution, update the interactive map's Version-specific data
and flow entries while preserving its UI shell, side panels, and click behavior.
Any UI redesign requires separate approval.
4. Update `CHANGELOG.md` if appropriate.
5. Report exactly which Markdown files were modified.
6. Report any documentation that still requires manual input, such as hardware photos, measurements, purchase links, or markings printed on a component.

Codex should not invent missing electronics details. If a board revision, GPIO safety note, voltage requirement, or module marking is unknown, it should remain documented as `TBD` until verified.

## Pull Request Handoff

If Codex asks the user to create a pull request, Codex must provide enough text for the user to paste directly into GitHub.

The handoff should include:

- branch name
- target branch
- pull request title
- ready-to-paste pull request description
- GitHub pull request creation link, if available

This is required when Codex has pushed a branch but cannot create the pull request because of GitHub tool or permission limitations.

## GitHub Pull Request Protection

The `main` branch is protected through a GitHub branch rule. Changes must be
merged through a pull request; no approving review is required while HomeOS has
only one maintainer. The rule also requires resolved conversations, disallows
force-pushes and branch deletion, and requires the `Build firmware` check.

The required workflow always starts for pull requests targeting `main`. It runs
the PlatformIO build only when firmware-related files, `platformio.ini`, or a
workflow file changes. Documentation-only pull requests skip the build job and
the skipped job reports success, so they are not blocked by an unnecessary
firmware build.

## Release Philosophy

HomeOS should always be releasable.

Avoid leaving the repository in a broken intermediate state. A release does not have to include every planned feature, but it should be internally consistent:

- firmware builds
- supported hardware assumptions are documented
- wiring notes match the implementation
- known limitations are written down
- the changelog reflects the milestone

The project should feel calm to return to after a gap of weeks or months. The documentation is what makes that possible.
