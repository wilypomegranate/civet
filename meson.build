project('civet', ['c', 'cpp'], default_options: ['warning_level=3', 'werror=true', 'cpp_std=c++17'])

qt5 = import('qt5')
qt5_dep = dependency('qt5', modules: ['Qml', 'Quick', 'Gui', 'Multimedia', 'Network'], private_headers: true)

# inc = include_directories('includes')
moc_files = qt5.compile_moc(headers : ['src/cpp/CursorMove.hpp', 'src/cpp/MouseClient.hpp', 'src/cpp/KeyboardClient.hpp'],
                            extra_args: ['-DMAKES_MY_MOC_HEADER_COMPILE'],
                            dependencies: qt5_dep)

qrc_cpp = qt5.compile_resources(sources: ['src/qml.qrc'])

wl_mod = import('unstable-wayland')
relative_pointer_protocol_xml = wl_mod.find_protocol('relative-pointer', state: 'unstable', version: 1)
relative_pointer = wl_mod.scan_xml(relative_pointer_protocol_xml, client: true, server: false)

wayland_client = dependency('wayland-client')

executable(
  'civet',
  moc_files,
  qrc_cpp,
  'src/cpp/main.cpp',
  'src/cpp/MouseClient.cpp',
  'src/cpp/KeyboardClient.cpp',
  'src/cpp/CursorMove.cpp',
  relative_pointer,
  dependencies: [qt5_dep, wayland_client]
)
