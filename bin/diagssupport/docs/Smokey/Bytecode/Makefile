.PHONY: default clean mostlyclean

COMMON_DIR = ../../LaTeX/
PACKAGES = \
	$(COMMON_DIR)Smokey.sty \
	$(COMMON_DIR)mylistings/listings.sty

PROJECT = Bytecode
ASSETS = # Add external images/etc here

export TEXINPUTS := $(TEXINPUTS):$(COMMON_DIR)
LATEX = xelatex '\gdef\CommonDir{$(COMMON_DIR)}\input{$1}' -o $2

default: $(PROJECT).pdf

$(PROJECT).pdf: \
	$(PROJECT).tex \
	$(PROJECT)Title.tex \
	$(PROJECT)Body.tex \
	$(ASSETS) \
	$(PACKAGES)

%.pdf: %.tex
	set -o errexit; \
	OldAuxHash=$$(md5 $(dir $@)/*.aux 2>/dev/null || true); \
	$(call LATEX,$<,$@); \
	NewAuxHash=$$(md5 $(dir $@)/*.aux 2>/dev/null || true); \
	if [ "$$OldAuxHash" != "$$NewAuxHash" ]; then \
		echo "******************************************************************************"; \
		$(call LATEX,$<,$@); \
	fi

clean: mostlyclean
	rm -f $(PROJECT).pdf

mostlyclean:
	rm -f *.aux *.log *.toc *.lof *.lol *.lot *.out
