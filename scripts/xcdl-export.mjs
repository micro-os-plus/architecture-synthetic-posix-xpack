/*
 * DO NOT EDIT!
 * Automatically generated from npm-packages-helper/templates/*.
 *
 * This file is part of the µOS++ project (https://micro-os-plus.github.io/).
 * Copyright (c) 2026 Liviu Ionescu. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose is hereby granted, under the terms of the MIT license.
 *
 * If a copy of the license was not distributed with this file, it can be
 * obtained from https://opensource.org/licenses/mit.
 */

// ----------------------------------------------------------------------------

import { readFileSync, writeFileSync, existsSync } from 'fs'
import { resolve, dirname, basename } from 'path'
import { fileURLToPath } from 'url'
import { Liquid } from 'liquidjs'
import json5 from 'json5'

// ----------------------------------------------------------------------------

const scriptPath = fileURLToPath(import.meta.url)
const scriptFolderPath = dirname(scriptPath)
const scriptName = basename(scriptPath)
const projectFolderPath = dirname(scriptFolderPath)

// ----------------------------------------------------------------------------

if (process.argv.length !== 3) {
  console.error(`Usage: ${scriptName} <xcdl-package.jsonc>`)
  process.exit(1)
}

const xcdlJsoncPath = process.argv[2]

console.log()
console.log(`Processing ${xcdlJsoncPath}...`)

// ----------------------------------------------------------------------------

const packageJsonPath = resolve(projectFolderPath, 'package.json')
if (!existsSync(packageJsonPath)) {
  console.error(`missing mandatory ${packageJsonPath}...`)
  process.exit(1)
}

if (!existsSync(xcdlJsoncPath)) {
  console.error(`missing mandatory ${xcdlJsoncPath}...`)
  process.exit(1)
}

// ----------------------------------------------------------------------------

const packageJson = JSON.parse(readFileSync(packageJsonPath, 'utf8'))
const xcdlJson = json5.parse(readFileSync(xcdlJsoncPath, 'utf8'))

// Topologically sort cdlComponents so that components referenced in
// another component's `dependencies` appear before that component.

if (Array.isArray(xcdlJson.cdlComponents)) {
  // The topological sort uses Kahn's algorithm:
  // It builds an in-degree map and a successors map from each component's 
  // dependencies (filtered to only IDs that exist within cdlComponents).
  // Components with no intra-list dependencies are enqueued first, then 
  // successors are unlocked as their prerequisites are emitted.
  // If a cycle is detected (sorted.length !== components.length), the 
  // script exits with an error.
  const components = xcdlJson.cdlComponents
  const known = new Set(components.map((c) => c.id))
  const inDegree = new Map(components.map((c) => [c.id, 0]))
  const successors = new Map(components.map((c) => [c.id, []]))

  for (const component of components) {
    for (const depId of component.dependencies ?? []) {
      if (known.has(depId)) {
        // depId must appear before component
        successors.get(depId).push(component.id)
        inDegree.set(component.id, inDegree.get(component.id) + 1)
      }
    }
  }

  const idToComponent = new Map(components.map((c) => [c.id, c]))
  const queue = [...inDegree.entries()]
    .filter(([, deg]) => deg === 0)
    .map(([id]) => id)
  const sorted = []

  while (queue.length > 0) {
    const id = queue.shift()
    sorted.push(idToComponent.get(id))
    for (const successorId of successors.get(id)) {
      const newDeg = inDegree.get(successorId) - 1
      inDegree.set(successorId, newDeg)
      if (newDeg === 0) {
        queue.push(successorId)
      }
    }
  }

  if (sorted.length !== components.length) {
    console.error('Circular dependency detected in cdlComponents!')
    process.exit(1)
  }

  xcdlJson.cdlComponents = sorted
}

const context = {
  libraryFilePath: xcdlJsoncPath,
  package: packageJson,
  xcdl: xcdlJson,
}

console.log()
console.log('"xcdl_context":')
console.log(JSON.stringify(context, null, 2))

// ----------------------------------------------------------------------------

const engine = new Liquid({
  strictFilters: true,
  strictVariables: true,
  lenientIf: true,
})

function substitute(fromFilePath, toFilePath) {
  console.log(`liquidjs -> ${toFilePath}`)
  const template = readFileSync(fromFilePath, 'utf8')
  const result = engine.parseAndRenderSync(template, context)
  writeFileSync(toFilePath, result)
}

// ----------------------------------------------------------------------------

const argv = process.argv.slice(2).join(' ')

console.log()
console.log('generating files...')
console.log()

substitute(
  resolve(scriptFolderPath, 'templates', 'CMakeLists-liquid.txt'),
  resolve(projectFolderPath, 'CMakeLists.txt')
)

substitute(
  resolve(scriptFolderPath, 'templates', 'meson-liquid.build'),
  resolve(projectFolderPath, 'meson.build')
)

console.log()
console.log(`'${scriptName} ${argv}' done`)

// ----------------------------------------------------------------------------
