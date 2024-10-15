#include "plug.h"
#include <cstdio>
#include <cstdlib>
#include <imgui.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN

#define EXPORT __declspec(dllexport)

#define PLUG(name, ret, ...) extern "C" EXPORT ret name(__VA_ARGS__);
LIST_OF_PLUGS
#undef PLUG

typedef struct {
  size_t size; // poor mans struct versioning
  ImGuiContext *ctx;
  // Custom state here
  int value;
  bool is_snd_window_open;
  float fvalue;
  int initalized_test;
  bool show_demo_window;
  // append only because I just check if the struct gets bigger
  char *input_text;
} Plug;

static Plug *p;

void plug_reset(void) {
  p->value = 0;
  p->fvalue = 0.f;
  p->is_snd_window_open = false;
  p->show_demo_window = false;
  p->input_text = nullptr;
}

void plug_init(ImGuiContext *ctx) {
  ImGui::SetCurrentContext(ctx);
  p = (Plug *)malloc(sizeof(*p));
  p->size = sizeof(*p);
  p->ctx = ctx;

  plug_reset();
}
// clean up allocations which are not part of the plug state
// Also destructors and stuff if needed
void *plug_pre_reload(void) { return p; }

void plug_post_reload(void *state) {
  p = (Plug *)state;
  if (p->size < sizeof(*p)) {
    printf("INFO: Migrating plug state schema %zu bytes -> %zu bytes\n",
           p->size, sizeof(*p));
    p = (Plug *)realloc(p, sizeof(*p));
    memset((char *)p + p->size, 0, sizeof(*p) - p->size);
    p->size = sizeof(*p);
  }
  ImGui::SetCurrentContext(p->ctx);
}

void plug_update(Env env) {
  ImGui::Begin("Test Plug");
  if (ImGui::Button("-")) {
    p->value--;
  }
  ImGui::SameLine();
  ImGui::Text("%d", p->value);
  ImGui::SameLine();
  if (ImGui::Button("+")) {
    p->value++;
  }
  if (ImGui::Button("Reset")) {
    plug_reset();
  }
  ImGui::Checkbox("Open another window", &p->is_snd_window_open);
  ImGui::Checkbox("Show Demo Window", &p->show_demo_window);
  if (!p->input_text) {
    p->input_text = (char *)malloc(512);
    memset(p->input_text, 0, 512);
  }
  ImGui::InputText("Random", p->input_text, 512);
  if (p->show_demo_window) {
    ImGui::ShowDemoWindow(&p->show_demo_window);
  }

  if (p->is_snd_window_open) {
    ImGui::Begin("Another one", &p->is_snd_window_open);
    ImGui::Text("Window size is: %.3f, %.3f", env.screen_width,
                env.screen_height);
    ImGui::SliderFloat("Any Value", &p->fvalue, 0.f, 20.f);
    ImGui::End();
  }
  ImGui::End();
}
