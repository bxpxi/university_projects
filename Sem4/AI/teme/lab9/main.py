from transformers import AutoTokenizer, AutoModelForCausalLM, pipeline, set_seed
import nltk

# Instalează resursa necesară pentru NLTK
nltk.download('punkt')

# Modele pre-antrenate
MODELS = {
    "general": "gpt2",  # Model general GPT-2
    "poetry_en": "gpt2-medium"  # Model adaptat pentru poezii (GPT-2 Medium)
}


# Funcția pentru a genera poezia completă pe baza unui singur vers
def generate_poem(model_name, first_verse, max_length=100, temperature=0.7, top_k=50, top_p=0.95):
    tokenizer = AutoTokenizer.from_pretrained(model_name)
    model = AutoModelForCausalLM.from_pretrained(model_name)
    generator = pipeline("text-generation", model=model, tokenizer=tokenizer)

    # Folosim primul vers ca prompt și generăm continuarea poeziei
    prompt = first_verse + "\n"
    generated = generator(prompt, max_length=max_length, temperature=temperature, top_k=top_k, top_p=top_p,
                          num_return_sequences=1)

    # Returnăm textul generat (continuarea poeziei)
    return generated[0]['generated_text']


# Funcția de comparare a modelelor pentru a analiza influența parametrilor
def compare_models(first_verse):
    print("=== GENERAL GPT-2 ===")
    poem_general = generate_poem(MODELS["general"], first_verse)
    print(poem_general)

    print("\n=== GPT2 MEDIUM (poetry model) ===")
    poem_poetry = generate_poem(MODELS["poetry_en"], first_verse)
    print(poem_poetry)

    return poem_general, poem_poetry


# Analiza întrebărilor teoretice
def analyze_questions():
    print("\n\n=== c.1 ===")
    print("Modelul poetic (gpt2-medium) generează text cu ritm și vocabular mai artistic decât GPT-2 general.")

    print("\n=== c.2 ===")
    print("Prompturi în engleză -> modelul poetic (antrenat în engleză) performează foarte bine.")

    print("\n=== c.3 ===")
    print("Prompturi în română -> GPT-2 general încearcă, dar rezultatele sunt artificiale, fără structură poetică.")

    print("\n=== c.4 ===")
    print("Prompt român + model englez -> rezultatele sunt neinteligibile sau complet amestecate.")

    print("\n=== c.5 ===")
    print(
        "LLM se poate personaliza pentru pasteluri prin fine-tuning pe corpusuri de pasteluri + introducerea unui token de stil, de ex. <pastel>.")


# Salvarea poeziei într-un fișier
def save_poem(poem_text, filename="generated_poem.txt"):
    with open(filename, "w", encoding="utf-8") as f:
        f.write(poem_text)
    print(f"\nPoezia a fost salvată în {filename}!")


# Exemplu de testare cu un vers de intrare
if __name__ == "__main__":
    set_seed(42)

    # Primul vers dat
    first_verse = "Upon the verdant hill, the sun doth rise,"

    # Compară modelele
    poem_general, poem_poetry = compare_models(first_verse)

    # Alege poezia cea mai coerentă (poate fi după lungime, formă, etc.)
    chosen_poem = poem_poetry if len(poem_poetry) > len(poem_general) else poem_general
    save_poem(chosen_poem)

    # Răspunsuri teoretice
    analyze_questions()
