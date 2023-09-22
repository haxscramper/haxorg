struct [[refl]] annotated {
    void cull_me() {}
};

int main() {
    annotated it;
    it.cull_me();
    it.call_me();
}
